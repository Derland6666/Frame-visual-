// src/main.cpp - Frame-Visual Geode Mod (Ultra Performance Edition)
#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/PlayerObject.hpp>

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <cmath>
#include <cstdio>
#include <cstdint>
#include <algorithm>

using namespace geode::prelude;

struct TimingStats {
    int earlyCount = 0;
    int midCount = 0;
    int lateCount = 0;
    int totalFrames = 0;
    
    void reset() { earlyCount = midCount = lateCount = totalFrames = 0; }
};

static TimingStats g_stats;

struct GlowData {
    CCSprite* sprite = nullptr;
    bool isSafe = false;
    float lastX = 0.0f;
    bool needsUpdate = true;
};

class SpritePool {
private:
    std::vector<CCSprite*> available;
    std::unordered_set<CCSprite*> inUse;
    
public:
    CCSprite* acquire() {
        CCSprite* sprite = nullptr;
        if (!available.empty()) {
            sprite = available.back();
            available.pop_back();
            sprite->setVisible(true);
        } else {
            sprite = CCSprite::createWithSpriteFrameName("d_effect_01_001.png");
            if (sprite) sprite->retain();
        }
        if (sprite) inUse.insert(sprite);
        return sprite;
    }
    
    void release(CCSprite* sprite) {
        if (!sprite) return;
        auto it = inUse.find(sprite);
        if (it != inUse.end()) {
            inUse.erase(it);
            sprite->setVisible(false);
            available.push_back(sprite);
        }
    }
    
    void cleanup() {
        for (auto s : available) if (s) s->release();
        for (auto s : inUse) if (s) s->release();
        available.clear(); inUse.clear();
    }
    ~SpritePool() { cleanup(); }
};

static SpritePool g_spritePool;

class SpatialGrid {
private:
    struct Cell { std::vector<GameObject*> objects; };
    std::unordered_map<int, Cell> grid;
    float cellSize = 100.0f;
    int getCellIndex(float x) const { return static_cast<int>(x / cellSize); }
    
public:
    void clear() { grid.clear(); }
    void insert(GameObject* obj) {
        if (obj) grid[getCellIndex(obj->getPositionX())].objects.push_back(obj);
    }
    void queryRange(float minX, float maxX, std::vector<GameObject*>& result) {
        int minCell = getCellIndex(minX);
        int maxCell = getCellIndex(maxX);
        result.clear();
        for (int i = minCell; i <= maxCell; ++i) {
            if (grid.contains(i)) {
                auto& objs = grid[i].objects;
                result.insert(result.end(), objs.begin(), objs.end());
            }
        }
    }
};

class $modify(FrameVisualPlayLayer, PlayLayer) {
    struct Fields {
        SpatialGrid spatialGrid;
        std::unordered_map<GameObject*, GlowData> glowCache;
        std::vector<GameObject*> queryBuffer;
        int currentFrame = 0;
    };

    bool init(GJGameLevel* level) {
        if (!PlayLayer::init(level)) return false;
        g_stats.reset();
        rebuildSpatialGrid();
        return true;
    }

    void rebuildSpatialGrid() {
        m_fields->spatialGrid.clear();
        if (!m_objects) return;
        for (unsigned int i = 0; i < m_objects->count(); ++i) {
            auto obj = static_cast<GameObject*>(m_objects->objectAtIndex(i));
            m_fields->spatialGrid.insert(obj);
        }
    }

    void update(float dt) {
        PlayLayer::update(dt);
        m_fields->currentFrame++;
        if (m_fields->currentFrame % 60 == 0) rebuildSpatialGrid();
    }
};

class $modify(FrameVisualPlayer, PlayerObject) {
    void pushButton(PlayerButton btn) {
        PlayerObject::pushButton(btn);
        if (!Mod::get()->getSettingValue<bool>("enabled")) return;
        auto pl = PlayLayer::get();
        if (!pl) return;
        auto fields = static_cast<FrameVisualPlayLayer*>(pl)->m_fields.self();
        float pX = this->getPositionX();
        std::vector<GameObject*> nearby;
        fields->spatialGrid.queryRange(pX, pX + 100.0f, nearby);
        auto color = Mod::get()->getSettingValue<ccColor3B>("glow-color-green");
        for (auto obj : nearby) { obj->setObjectColor(color); }
    }
};
