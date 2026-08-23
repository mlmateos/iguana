
# Iguana

**An IDE for LaTeX with AI Corpus Integration — fork of TeXstudio.**

Iguana extends TeXstudio with a **Build Corpus** feature that turns LaTeX books into auditable, provenance-rich Markdown suitable for AI training — compatible with the [OpenWALDO](https://github.com/openwaldo) commons.

## ✨ Features

- **Build Corpus**: One-click LaTeX → Markdown pipeline via [tex2waldo](https://github.com/mlmateos/tex2waldo).
  - Acts on the **Root Document** (not the active file).
  - Preserves full provenance: Zenodo DOIs, CC-BY-4.0 licensing, author attribution.
  - Generates a `.pandoc.log` for inspection.
  - On error, opens the flattened `.pandoc/` artifact for diagnosis.
  - On success, opens the resulting `.md` with your default viewer.
- **Rebranded UI**: Custom logo, splash screen, and dark-mode palette (Emerald green + Jacaranda accents).
- **Help links**: LaTeX Reference (Wikibooks) and User Manual (GitHub).

Everything else you love from TeXstudio — syntax highlighting, live PDF preview, structure view, Git integration, spell/grammar checking — is still there.

## 🛠 Building from source

Iguana uses the same build system as TeXstudio (CMake + Qt 6).

```bash
git clone https://github.com/mlmateos/iguana.git
cd iguana
mkdir build && cd build
cmake .. -DTEXSTUDIO_USE_QT6=ON
make -j$(nproc)
./iguana
```

See [`BUILD.md`](BUILD.md) for full dependencies (Poppler, Qt 6.8 LTS, Python 3.13).

## 🔗 Companion project

Iguana's Build Corpus feature relies on **[tex2waldo](https://github.com/mlmateos/tex2waldo)**, the LaTeX → Markdown pipeline for producing auditable AI training corpora.

## 🗺 Roadmap to 1.0

- [ ] Sidebar and taskbar icon integration
- [ ] UI refinement for the Build Corpus toolbar button
- [ ] Language tagging (`es-MX`) in corpus manifest
- [ ] AppImage distribution (glibc ≥ 2.38)
- [ ] Qt 6.8 LTS build matrix

## 📄 License

GPL-3.0 — same as TeXstudio. See [`COPYING`](COPYING).

## 🙏 Credits

- Original TeXstudio project and its contributors.
- The Zapotec community of Juchitán, whose philosophy and language live in the first book processed with this tool.

---

## 🤖 Acknowledgments
This project was developed with the assistance of [Qwen](https://qwenlm.github.io/), a large language model by Alibaba Group.
