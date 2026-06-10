# POS System in C++ / C

POS system that manages inventory and users, handles authentication, and tracks sales. The C++ version was developed for the **Structured Programming** course at UNIVA.

The project has two versions:

The primary difference besides the programming language is the way they store data. The C++ version is hardcoded, while C version has file persistence.

## Features

- User authentication with role-based access (administrator / sales)
- Inventory management — add, remove, search, modify products
- Inventory display sorted by ID or name using Bubble Sort
- Automatic reorder level alerts
- Sales registration with ticket generation and cash cut
- User account management — add, remove, modify accounts

## Data structures used

| Structure | Use |
|---|---|
| Parallel arrays | Base storage for inventory and users |
| `struct Inventario` | Individual product representation |
| `struct Venta` | Products in a single sale |
| Linked list (`struct Nodo`) | Dynamic user management |

Both versions keep arrays, structs, and linked list in sync on every operation.

## Credentials (C++ version)

| User | Password | Role |
|---|---|---|
| admin1 | 1234 | Administrator |
| ventas2 | 1234 | Sales |

> Credentials are hardcoded for demo purposes only.

## Project structure

```
pos-system/
├── cpp/
│   └── main.cpp
├── c/
│   ├── main.c
│   └── data/
│       ├── productos.txt
│       └── usuarios.txt
└── README.md
```

> The C version looks for data files inside the `data/` folder relative to where the program is executed.

## Academic context

Final project for **Structured Programming** — Systems Engineering, UNIVA.
