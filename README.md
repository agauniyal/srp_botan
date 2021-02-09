# srp_botan
Minimal SRP Server/Client classes using Botan

----

## Build Executable (skip if only building WASM)
```
mkdir build && cd build
conan install ..
cmake ..
cmake --build .
```

## Build WASM
You'll need to clone and build botan in separate directory -
```
git clone https://github.com/randombit/botan.git
CXX=em++ ./configure.py --cc=clang --cpu=llvm --os=emscripten
make -j16
```

Once built you can cd back to this project's directory
```
em++ -std=c++17 --bind -s ALLOW_MEMORY_GROWTH=1 -s WASM=1 -I../botan/build/include ../botan/libbotan-3.a srp_server_client.cpp -o a.html
```

You can now run a local http server and open a.html file in browser. Exposed classes should be available on `Module` object.
