# Project Compilation Guide

## Overview
This guide provides the necessary steps to compile the C++ project that includes multiple source files grouped under different subdirectories such as leptons, bosons, and quarks.

## Requirements
- GCC Compiler (g++.exe) installed via MSYS2 with the ucrt64 environment.
- Make sure that all the prerequisites are installed and paths are set correctly.

## Compilation
To compile the project, use the following command line in your MSYS2 terminal. Navigate to the project directory where your source files are located and execute the command:

```bash
C:\\msys64\\ucrt64\\bin\\g++.exe -fdiagnostics-color=always -g "${workspaceFolder}\\leptons/Muon.cpp" "${workspaceFolder}\\leptons/Electron.cpp" "${workspaceFolder}\\leptons/Lepton.cpp" "${workspaceFolder}\\leptons/Tau.cpp" "${workspaceFolder}\\leptons/Neutrino.cpp" "${workspaceFolder}\\bosons/Boson.cpp" "${workspaceFolder}\\bosons/Gluon.cpp" "${workspaceFolder}\\bosons/Photon.cpp" "${workspaceFolder}\\bosons/Z.cpp" "${workspaceFolder}\\bosons/W.cpp" "${workspaceFolder}\\bosons/Higgs.cpp" "${workspaceFolder}\\quarks/Quark.cpp" "${workspaceFolder}\\FourMomentum.cpp" "${workspaceFolder}\\Particle.cpp" "${workspaceFolder}\\helper_functions.cpp" "${workspaceFolder}\\showcase.cpp" "${workspaceFolder}\\user_interface.cpp" "${workspaceFolder}\\project.cpp" -o "${workspaceFolder}\\project"

