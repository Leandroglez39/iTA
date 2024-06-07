# iTA

## Repository structure

- `data/`: contains the data will be used in the project
- `benchmarks/`: contains the benchmarks that was used in the project
- `output/`: contains the output of the project
- `Algorithms.sln`: the solution file of the project in Visual Studio
- `Algorithms/`: the project folder

## How to run the project

1. Open the solution file `Algorithms.sln` in Visual Studio, recommended version is Visual Studio 2022 or later.
2. Build the project.
3. Run the project.
4. The output will be saved in the `output/` folder.

### Note

- Once the project is opened in Visual Studio, the main file is `Algorithms.cpp` in the `Algorithms/` folder. You can run the project by running this file. In this file, you can change the input data, the number of iterations and the output file.
- The project is written in C++. Is necessary to have a C++ compiler into Visual Studio to run the project.
- The project uses the `OpenMP` library to parallelize the code. Make sure that the `OpenMP` library is installed in your Visual Studio and is enabled in the project settings.
