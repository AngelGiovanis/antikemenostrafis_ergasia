# Self-Driving Car Simulation (C++)

## Overview

This project is a simplified simulation of a self-driving car system in a grid-based world. The simulation includes moving cars, bikes, parked cars, traffic lights, and stop signs. Users can configure the world, number of objects, and GPS waypoints through command-line arguments.

---

## Project Structure

antikemenostrafis_ergasia/
├── include/
│   └── types.h        # Class declarations
├── src/
│   ├── types.cpp      # Class implementations
│   └── main.cpp       # Main simulation driver
├── Makefile           # Build instructions
└── README.md          # This file

### Key Classes

- `parameters` — Holds simulation parameters (world size, object counts, GPS targets, etc.). Parses command-line arguments and provides debug printing.  
- `grid_world` — Represents the 2D grid map and dynamically allocates a 2D array.  
- `position` — Stores `(x, y)` coordinates.  
- `self_driving_car` — Represents a moving car with speed and navigation behavior.  
- `trafic_light` — Represents a traffic light with state changes over simulation ticks.  
- `object` — Base class for static/dynamic objects like traffic signs, lights, and cars.  

---

## Build Instructions

Use the provided Makefile. From the project root:

```bash
make
