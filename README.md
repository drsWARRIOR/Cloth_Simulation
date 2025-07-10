
# Cloth Simulation

A 2D cloth simulation built in C++ using SFML, based on Verlet Integration. This project serves as a learning implementation to understand the fundamentals of physics simulation.

## Contents

- [Overview](#Overview)
- [Building Instructions](#Building_Instructions)
- [Features](#Features)

## Overview

This Cloth Simulation demonstrates how a grid of interconnected particles can be simulated to behave like cloth using Verlet Integration, a numerical methos used to solve second-order ordinary differential equations (ODEs), particularly those that arise in Newtonian mechanics.

The simulation uses SFML for rendering, window and input.

<a name="Building_Instructions"></a>
## Building Instructions

The project supports Microsoft Windows, Linux, and Mac

### Windows Building Instructions

Project supports MSVC/Visual Studio and MinGW

 You will need [Git](https://git-scm.com/downloads), [Cmake](https://cmake.org/download/), [Visual Studio](https://visualstudio.microsoft.com/) / [MinGW](https://sourceforge.net/projects/mingw/)

#### MSVC and Visual Studio (Recommended)

1. Clone the repository
``` 
git clone --recurse-submodules https://github.com/drsWARRIOR/Cloth_Simulation.git
```

2. Create the Folder for building, and build the project in the folder using CMake
``` 
mkdir build
cd build
cmake .. -G "Visual Studio 17 2022"
```

3. Once the building process is complete, a Visual Studio Solution will be generated. Open the Visual Studio solution file named "Cloth_Simulation.sln"

``` 
.\Cloth_Simulation.sln
```

4. Once the Solution is opened, find the project named as "Cloth_Simulation" in the solution explorer, and right click on it and select the option "Set as Startup Project" from the dropdown menu. This will set the main Cloth_Simulation project as the Startup project

5. Build the solution and run the Project

#### MinGW

*Coming Soon*

### Linux Building Instructions

To build on Linux, you will need git, cmake, gcc, and SFML building prerequisites

#### Debian

- Prerequisite installation

1. This command installs GCC, Git, CMake, and all SFML building prerequisites
```
sudo apt install -y build-essential cmake git libfreetype6-dev libx11-dev libxrandr-dev libxcursor-dev libxi-dev libudev-dev libgl1-mesa-dev libflac-dev libogg-dev libvorbis-dev libvorbisenc2 libvorbisfile3 libpthread-stubs0-dev
```
2. Clone the git repository, and open the clone directory
```
git clone --recurse-submodules https://github.com/drsWARRIOR/Cloth_Simulation.git 
cd Cloth_Simulation
```

3. Create the Folder for building, and build the project in the folder using CMake
```
mkdir build
cd build
cmake ..
make
```
4. Now that the building is completed, you can run the Cloth_Simulation file in /build/bin/ directory

```
./bin/Cloth_Simulation
```

### Mac Building Instructions

To build on mac, you will need git, cmake, CLang

#### Debian

- Prerequisite installation

1. This command installs command line tools.
```
xcode-select --install
```
2. This command will install git and cmake
```
brew install cmake git
```
*Note: Makesure to install homebrew before running this command*

3. Clone the git repository, and open the clone directory
```
git clone --recurse-submodules https://github.com/drsWARRIOR/Cloth_Simulation.git 
cd Cloth_Simulation
```

4. Create the Folder for building, and build the project in the folder using CMake
```
mkdir build
cd build
cmake ..
cmake --build .
```
5. Now that the building is completed, you can run the Cloth_Simulation file in /build/bin/ directory

```
./bin/Cloth_Simulation
```

## Features

![1751906653974381](https://github.com/user-attachments/assets/c91650e3-cf54-4f8f-8b14-fdfc2ec8673b)

- **Verlet Integration Based Simulation**  
  A physics simulation that updates particle positions using previous states rather than velocities, making it stable and intuitive for constraints like cloth.

- **Constraint Satisfaction System**  
  Each point is connected via constraints (simulating threads), and the simulation repeatedly solves these to ensure the cloth behaves naturally.

- **Tearing & Pinning (Future Scope)**  
  Particles can be pinned (fixed position), and can be destroyed based on user input which simulates a tearing effect

## Reference
If you want to learn more about verlet integration and cloth simulation logic, here is a great article from [pikuma](https://pikuma.com/blog/verlet-integration-2d-cloth-physics-simulation)

