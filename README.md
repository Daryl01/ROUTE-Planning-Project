# ROUTE-Planning-Project
This repo contains the code to find the shortest path between two points on a IO2D Map

![path rendered](https://user-images.githubusercontent.com/30718789/187646240-88770878-5fd0-4603-b6d2-27a05351f688.png)

## Dependencies for Running Locally
* cmake >= 3.11.3
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
* gcc/g++ >= 7.4.0
* IO2D
  * Installation instructions for all operating systems can be found [here](https://github.com/cpp-io2d/P0267_RefImpl/blob/master/BUILDING.md)
  * This library must be built in a place where CMake `find_package` will be able to find it
  
## Compiling and Running

### Compiling
To compile the project go inside the `build` directory, then run `cmake` and `make` as follows:
```
cmake ..
make
```
### Running
The executable will be placed in the `build` directory. From within `build`, you can run the project as follows:
```
./OSM_A_star_search
```
Or to specify a map file:
```
./OSM_A_star_search -f ../<your_osm_file.osm>
```

## Testing

The testing executable is also placed in the `build` directory. From within `build`, you can run the unit tests as follows:
```
./test
```
Successful test should display the following information
![test](https://user-images.githubusercontent.com/30718789/187648840-3daa4456-efe5-42a0-92fc-c26e444a3a74.PNG)
