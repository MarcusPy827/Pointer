# marcus.pointer.app

An Electron application with React and TypeScript

## Recommended IDE Setup

- [VSCode](https://code.visualstudio.com/) + [ESLint](https://marketplace.visualstudio.com/items?itemName=dbaeumer.vscode-eslint) + [Prettier](https://marketplace.visualstudio.com/items?itemName=esbenp.prettier-vscode)

## Project Setup

### Install

```bash
$ npm install
```

Make sure you have cloned the git repo of Abseil, then `cd` to the repo and run:

```bash
$ cmake -B build -DCMAKE_BUILD_TYPE=Release \
  -DBUILD_SHARED_LIBS=OFF \
  -DABSL_BUILD_TESTING=OFF \
  -DABSL_PROPAGATE_CXX_STD=ON \
  -DCMAKE_CXX_STANDARD=20 \
  -DCMAKE_POSITION_INDEPENDENT_CODE=ON\
  -DCMAKE_CXX_FLAGS="-fPIC"
$ cmake --build build -j
$ sudo cmake --install build
```
Then copy the library:

```bash
$ chmod +x ./scripts/copy_library.sh
$ ./scripts/copy_library.sh
```

### Development

```bash
$ npm run dev
```

### Build

```bash
# For windows
$ npm run build:win

# For macOS
$ npm run build:mac

# For Linux
$ npm run build:linux
```
