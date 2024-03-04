#!/bin/bash

# Compile source files
g++ -c main.cpp -o main.o $(pkg-config --cflags --libs mysqlclient)
g++ -c Appointment.cpp -o Appointment.o $(pkg-config --cflags --libs mysqlclient)
g++ -c Doctor.cpp -o Doctor.o $(pkg-config --cflags --libs mysqlclient)
g++ -c Hospital.cpp -o Hospital.o $(pkg-config --cflags --libs mysqlclient)
g++ -c Hospitalization.cpp -o Hospitalization.o $(pkg-config --cflags --libs mysqlclient)
g++ -c Patient.cpp -o Patient.o $(pkg-config --cflags --libs mysqlclient)
g++ -c Specialization.cpp -o Specialization.o $(pkg-config --cflags --libs mysqlclient)
g++ -c User_Details.cpp -o User_Details.o $(pkg-config --cflags --libs mysqlclient)
g++ -c IDtoName.cpp -o IDtoName.o $(pkg-config --cflags --libs mysqlclient)

# Link object files to create executable
g++ main.o Appointment.o Doctor.o Hospital.o Hospitalization.o Patient.o Specialization.o User_Details.o IDtoName.o -o carealign $(pkg-config --cflags --libs mysqlclient)

# Run the executable
./carealign

