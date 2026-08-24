# UIT3562 – Principles of Operating Systems

C programs and laboratory work completed for the **UIT3562 – Principles of Operating Systems** course.

This repository contains programs developed during the Operating Systems laboratory sessions, covering system calls, CPU scheduling, inter-process communication, and other OS concepts.

## 📚 Course Details

* **Course Code:** UIT3562
* **Course Name:** Principles of Operating Systems
* **Language:** C
* **Compiler:** GCC
* **Platform:** Linux / Ubuntu

## 📁 Repository Structure

```text
sem-5-os-lab/
│
├── inter_process_communication/
│   ├── pipes/
│   │   └── pipe.c
│   │
│   ├── message_queue/
│   │   ├── ipc_mq_sender.c
│   │   ├── ipc_mq_receiver.c
│   │   └── sample.txt
│   │
│   ├── shared_memory/
│   │   └── ipc_sm.c
│   │
│   └── semaphores/
│       └── ipc_semp.c
│
├── menu_driven_program/
│   ├── menu_driven_program.c
│   └── sample.txt
│
├── miscellaneous/
│   ├── main.c
│   ├── main1.c
│   ├── main2.c
│   ├── main3.c
│   ├── main4.c
│   ├── main5.c
│   ├── main6.c
│   ├── main7.c
│   ├── main8.c
│   └── main9.c
│
├── scheduling_algorithms/
│   ├── fcfs_array_implementation.c
│   │
│   ├── FCFS/
│   │   └── fcfs.c
│   │
│   ├── SJF_P/
│   │   └── sjf_p.c
│   │
│   ├── SJF_NP/
│   │   └── sjf_np.c
│   │
│   ├── PS_P/
│   │   └── priority_scheduling_p.c
│   │
│   ├── PS_NP/
│   │   └── priority_scheduling_np.c
│   │
│   └── RR/
│       └── round_robin.c
│
├── system_calls_programming/
│   ├── scp1/
│   │   ├── scp_1a.c
│   │   ├── scp_1b.c
│   │   ├── scp_1c.c
│   │   ├── scp_1d.c
│   │   └── scp_1e.c
│   │
│   ├── scp2/
│   │   ├── scp_2a.c
│   │   ├── scp_2b.c
│   │   └── scp_2c.c
│   │
│   ├── scp3/
│   │   ├── scp_3a.c
│   │   ├── scp_3b.c
│   │   └── output.txt
│   │
│   └── scp4/
│       ├── scp_4a.c
│       ├── a.txt
│       ├── b.txt
│       ├── project/
│       │   ├── file1.txt
│       │   └── file2.c
│       │
│       ├── mini_project/
│       │   └── mini_project.c
│       │
│       └── report/
│           └── mini_project_report.txt
│
├── lab_record_first_four_experiments.docx
│
└── README.md
```

## 🧪 Topics Covered

### 1. System Calls Programming

Programs demonstrating the use of Linux system calls and low-level OS functionality.

```text
system_calls_programming/
├── scp1/
├── scp2/
├── scp3/
└── scp4/
```

These experiments include multiple programs involving file and process-related system-level operations.

### 2. CPU Scheduling Algorithms

Implementations of commonly studied CPU scheduling algorithms:

* **FCFS** – First Come First Serve
* **SJF (Preemptive)** – Shortest Job First
* **SJF (Non-Preemptive)**
* **Priority Scheduling (Preemptive)**
* **Priority Scheduling (Non-Preemptive)**
* **Round Robin**

The repository also contains an array-based FCFS implementation.

### 3. Inter-Process Communication

Programs demonstrating different IPC mechanisms available in Linux:

* **Pipes**
* **Message Queues**
* **Shared Memory**
* **Semaphores**

```text
inter_process_communication/
├── pipes/
├── message_queue/
├── shared_memory/
└── semaphores/
```

### 4. Menu-Driven Program

A menu-driven C program demonstrating file/program operations through an interactive interface.

### 5. Miscellaneous Programs

Additional C programs developed during laboratory sessions and practice.

## ⚙️ Compilation

Programs can generally be compiled using GCC:

```bash
gcc program.c -o program
```

Run the compiled program:

```bash
./program
```

For example:

```bash
cd scheduling_algorithms/FCFS
gcc fcfs.c -o fcfs
./fcfs
```

For programs using multiple source files:

```bash
gcc file1.c file2.c -o program
```

## 🐧 Environment

The programs are primarily developed and tested on a Linux environment.

```text
OS       : Ubuntu Linux
Compiler : GCC
Language : C
VCS      : Git
```

Some programs use Linux/POSIX system calls and therefore may require a Linux environment for compilation and execution.

## 📖 Lab Record

The repository also contains the record for the first four experiments:

```text
lab_record_first_four_experiments.docx
```

## 🎯 Purpose

This repository is maintained as a collection of **Operating Systems laboratory programs**, serving as:

* A record of laboratory work
* A reference for revision
* A place to maintain implementations of OS concepts
* A reference for practical examinations

## 👨‍💻 Author

**Sree**

B.Tech Information Technology
