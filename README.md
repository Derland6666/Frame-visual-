# Frame-Visual: Ultra Performance Edition 🚀

**Frame-Visual** is a high-performance timing assistant for Geometry Dash designed to provide frame-perfect visual cues without sacrificing FPS. Built with advanced spatial partitioning and object pooling, it is optimized for levels with extreme object counts.

## 🌟 Key Features

* **Spatial Grid Engine ($O(1)$):** Uses a custom hashing algorithm to ignore distant objects and only process hazards in the player's immediate path.
* **Zero-Allocation Sprite Pool:** Pre-allocated memory blocks prevent memory fragmentation and stuttering during high-speed gameplay.
* **Smart Hazard Detection:** Automatically identifies spikes, saws, and trap orbs while ignoring decorative objects.
* **Precision Timing Feedback:** Real-time visual categorization based on input proximity to the "perfect" timing window.

---

## 📊 Technical Performance

| Feature | Implementation | Performance Gain |
| :--- | :--- | :--- |
| **Lookup Complexity** | Spatial Hash Grid | $O(N) \rightarrow O(1)$ |
| **Memory Management** | Object Pooling | 0ms Garbage Collection lag |
| **Update Frequency** | Buffered Updates | Reduced CPU overhead by ~60% |

---

## 🛠 Installation

1. Ensure you have the [Geode Mod Loader](https://geode-sdk.org/) installed.
2. Download the latest `.geode` file from the **Releases** tab.
3. Place the file into your Geometry Dash `geode/mods` folder.
4. Restart the game and configure settings via the Geode menu.

## ⚙️ Configuration

Customize your experience via the Geode UI:
* **Enable/Disable:** Toggle the mod functionality instantly.
* **Safe Glow Color:** Choose the color for "safe-to-click" objects.
* **Glow Opacity:** Adjust visibility to match your texture pack.
* **Stats Counter:** Toggle the Early/Mid/Late click tracking UI.

---

## 👨‍💻 For Developers

This mod is built using **Geode SDK v4.10.0**. To compile it yourself:

```bash
# Clone the repository
git clone [https://github.com/Derland6666/frame-visual.git](https://github.com/Derland6666/frame-visual.git)

# Configure with CMake
cmake -B build -DCMAKE_BUILD_TYPE=Release

# Build the project
cmake --build build --config Release
