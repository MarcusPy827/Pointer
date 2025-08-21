# File Handler
## How to Complie
This application depends on these libraries, you'll need to have them avaliable in your search path:

### Abseil
First, clone the Abseil git library.

Make sure CMake is avaliable in your system, then change directory to the location where you have cloned the Abseil source code:

```Shell
cd /path/to/abseil/git/source/cloned/
```

Next, use CMake to install it. Here is an example of how you can install the library on Windows, please ENSURE that you have a complier that is able to work with C17 standard:

```bat
cmake -B build -S .  -DCMAKE_BUILD_TYPE=Release  -DCMAKE_CXX_STANDARD=17  -DCMAKE_CXX_STANDARD_REQUIRED=ON  -DABSL_PROPAGATE_CXX_STD=ON  -DCMAKE_INSTALL_PREFIX="C:/local/absl"
```

```bat
cmake --build build --config Release
```

```bat
cmake --install build --config Release
```

**Note**: You may set `DCMAKE_INSTALL_PREFIX` to any directory you finds suitable.

## Complie the Unit Test
Ensure that you have already installed all the libraries, if you have all the libraries in your system/environment PATH then you can skip this paragraph; If NOT, then edit the `deps.cmake` file:

```cmake
set(absl_DIR "C:/local/absl/lib/cmake/absl")
set(absl_ROOT "C:/local/absl/lib/cmake/absl")
```

**Note**: The path here is an example, you'll need to change it to the actual path.

Then, you may complie the unit test using CMake.
