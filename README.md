# Software Renderer
This is a toy 3D software renderer, it uses SDL and no other graphics libraries.

At the moment it does back-face culling, point light sources with flat shading and z-buffering.

The model namespace includes method to produce a cube, an octahedron and a sphere using a subdivided octahedron based on the tutorial from [binpress](http://www.binpress.com/tutorial/creating-an-octahedron-sphere/162).

The code can be compiled on OSX with clang, as well as for the Dingoo. However, on the Dingoo it is incredibly slow mainly because the Dingoo doesn't have an FPU. I plan to move over to fixed point math soon.

## Compiling
Note that the code is C++11 compliant, however it has been only been tested with clang++ for OSX and with mipsel-linux-g++ for the Dingoo when running Dingux.


### OSX
```shell
make osx
```

### Dingoo (running Dingux)
Ensure that you've installed the Dinguz toolchain, found here: [Dingux toolchain](http://wiki.dingoonity.org/index.php?title=Development:Tutorials:HelloWorld) then:
```shell
make dingoo
```

## Tests
The project uses the excellent Bandit unit testing framework available at [banditcpp]{http://banditcpp.org} under the MIT license.

To compile the tests for OSX do:

```shell
make test_osx
```

To compile for the Dingoo do:

```shell
make test_dingoo
```
