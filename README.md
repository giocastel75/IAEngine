# IAEngine

A minimal C application that loads a GGUF model via [llama.cpp](https://github.com/ggerganov/llama.cpp) and confirms it was loaded successfully. Early-stage project — model loading only, no inference yet.

## Build

llama.cpp is included as a git submodule.

```sh
git clone --recurse-submodules https://github.com/giocastel75/IAEngine.git
cd IAEngine
cmake -B build
cmake --build build
```

If you already cloned without `--recurse-submodules`:

```sh
git submodule update --init --recursive
```

## Usage

```sh
./build/bin/IAEngine <model.gguf>
```

Model files (`.gguf`) are not tracked in this repository — download one separately (e.g. from Hugging Face) and pass its path as the argument.

## License

MIT — see [LICENSE](LICENSE).
