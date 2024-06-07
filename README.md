# iTA

> Process Mining is a computational discipline focused on discovering, monitoring, and improving processes. In the business sector, this discipline combines artificial intelligence techniques with data mining algorithms. Together, they excel at uncovering trends, patterns, and details within classified data systems. Within this domain, the Trace Alignment algorithm emerges as a pivotal tool. It specializes in detecting anomalies in patterns and pointing out similarities. Most existing implementations of this algorithm adopt a progressive alignment approach, which incurs a high computational cost. We propose a novel implementation of the Trace Alignment algorithm with significant theoretical modifications. Advanced programming and parallelism techniques have been incorporated. The algorithm's execution times have been optimized to a polynomial order, showcasing a marked improvement from previous implementations. The validation of our results confirms both the efficiency and the expected quality of the alignment.

```bash

iTA/
├── Algorithms/
│   ├── Algorithms.cpp
│   ├── Algoritmos.cpp
│   ├── edlib.cpp
│   ├── Input.cpp
│   ├── mstar.cpp
│   ├── Nj.cpp
│   ├── normal-NW.cpp
│   ├── Refine.cpp
│   ├── Tools.cpp
│   ├── _editdistance.cpp
├── data/
├── outputs/
├── benchmarks/
│   ├── Balibase
│   ├── Homstrad
│   ├── OxBench
├── .gitignore
├── README.md
├── Algorithms.sln
└── CppProperties.json
```

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
