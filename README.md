# Software Renderer
This is a toy 3D software renderer, it uses SDL and no other graphics libraries.

At the moment it does back-face culling, point light sources with flat shading and z-buffering.

The model namespace includes method to produce a cube, an octahedron and a sphere using a subdivided octahedron based on the tutorial from [binpress](http://www.binpress.com/tutorial/creating-an-octahedron-sphere/162).

The code can be compiled on OSX with clang, as well as for the Dingoo. However, on the Dingoo it is incredibly slow mainly because the Dingoo doesn't have an FPU. I plan to move over to fixed point math soon.
