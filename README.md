# circom runtime

This is the code needed to calculate the witness by a circuit compiled with [circom](https://github.com/iden3/circom).

## Server
To compile server implementation:
- Compile Server
```
g++ -O3 -std=c++17 -DSERVER_ENABLE -fopenmp -pthread calcwit.cpp main.cpp utils.cpp fr.cpp fr.o socket.cpp circuit-1960-32-256-64.cpp  -o circuit-1960-32-256-64 -lgmp
```
- Compile Client
```
g++ -std=c++17 client.cpp socket.cpp -o client
```
- Launch Server
```
./circuit-1960-32-256-64
```
- Launch Client
```
./client input-1960-32-256-64.json circuit-1960-32-256-64_w.wshm
```


## License 

Circom is part of the iden3 project copyright 2018 0KIMS association and published with Apache-2 license. Please check the COPYING file for more details.
