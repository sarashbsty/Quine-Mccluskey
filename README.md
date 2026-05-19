## Quine-McCluskey 
A simple Boolean minterms Expression solver. It takes JSON text input and outputs JSON text with Minimized Expression, grouping and reduction data, 
prime-Implicants, Essential Implicants, Uncovered Minterms, Column Domination and Petrick Process

## Input Struture Example
{"var": 4, "minterms":[1,2,3,4,5,6], "dontCares":[2,3]}
note: dontcares is optional, can be omitted

## Build guide for webAssembly

Prerequisite: emcmake and cmake must be installed and configured beforeHand.
- step1 : Download the zip or clone the repository.
- step2 : Open terminal in the root of the project.
- step3 : Run "emcmake cmake -S . -B build-wasm"     
         The terminal will show 'configaration done' , 'generation done' if completed successfully.
- step4:  Run "cmake --build build-wasm" . 
          The terminal will show progress of compilations.
- After Completing above steps, two files will be created inside the root of the project. - "quine.js" and "quine.wasm" .

<img width="1447" height="237" alt="image" src="https://github.com/user-attachments/assets/a572553d-424a-4f0d-a807-98007be8a473" />
<img width="1193" height="632" alt="image" src="https://github.com/user-attachments/assets/283fca5e-61f6-441a-a5a1-4c5fc511ea19" />

##Build guide for CLI

Prerequisite: cmake must be installed and configured beforeHand.
- step1 : Download the zip or clone the repository.
- step2 : Open terminal in the root of the project.
- step3 : Run "cmake -S . -B build"     
         The terminal will show 'configaration done' , 'generation done' if completed successfully.
- step4:  Run "cmake --build build" . 
          The terminal will show progress of compilations.
- After Completing above steps, a .exe files will be created inside the root of the project. - "quine.exe" .

<img width="1202" height="357" alt="image" src="https://github.com/user-attachments/assets/a580b261-9f48-4d23-b5b3-c2ee726d0918" />
<img width="1195" height="157" alt="image" src="https://github.com/user-attachments/assets/3424bcb7-9dd4-4cb3-a130-22235e0baaf5" />



CLI output Example (same json output in text by webAssembly module):
<img width="1307" height="158" alt="image" src="https://github.com/user-attachments/assets/c194ddce-e807-42e9-9185-76661539457a" />
<img width="1136" height="963" alt="image" src="https://github.com/user-attachments/assets/32cc73a3-9081-473f-9842-f6b091dabb09" />
<img width="1125" height="962" alt="image" src="https://github.com/user-attachments/assets/6444de73-7fdd-4d90-ae15-ba6d05fdf58e" />
<img width="1121" height="142" alt="image" src="https://github.com/user-attachments/assets/0896abd6-c751-471c-b003-c5c27b07bdcf" />












