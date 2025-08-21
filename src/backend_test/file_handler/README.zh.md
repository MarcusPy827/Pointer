# File Handler
## 如何编译
此程序依赖以下第三方库，您需要安装这些库：

### Abseil
首先，克隆Abseil的代码到本地。

确保CMake在系统上可用，然后`cd`至Abseil源代码的位置：

```Shell
cd /path/to/abseil/git/source/cloned/
```

然后，使用CMake编译并安装这个库。以下是Windows上的示例，请确保系统上有一个可以编译C17标准的编译器：

```bat
cmake -B build -S .  -DCMAKE_BUILD_TYPE=Release  -DCMAKE_CXX_STANDARD=17  -DCMAKE_CXX_STANDARD_REQUIRED=ON  -DABSL_PROPAGATE_CXX_STD=ON  -DCMAKE_INSTALL_PREFIX="C:/local/absl"
```

```bat
cmake --build build --config Release
```

```bat
cmake --install build --config Release
```

**注意**：您可以设置`DCMAKE_INSTALL_PREFIX`为任何您觉得合适的目录。

## 编译单元测试
确保上述第三方库已经被正确安装，如果这些库在系统/环境PATH中均可用，那么您可以跳过此部分；否则，您需要按需编辑`deps.cmake`文件：

```cmake
set(absl_DIR "C:/local/absl/lib/cmake/absl")
set(absl_ROOT "C:/local/absl/lib/cmake/absl")
```

**注意**：这里的路径仅为示例，您需要换为当前环境下各个库的实际路径。

然后，您就可以使用CMake编译单元测试了。
