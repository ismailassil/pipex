# PIPEX
pipex is a 42 school project that implements a simplified version of the Unix pipeline (|) command. It demonstrates inter-process communication by using pipes to connect the standard output of one process to the standard input of another. The project involves creating a custom program that can handle multiple commands in a pipeline, manage file descriptors, and execute external programs.

### Processes

A Process is a instance of execution of a program. When  a program is executed, the Kernel loads the code into virtual memory,  allocates space for program variables, and sets up kernel bookkeeping data structure to record various informations about the process. *(PID [process id], PPID [parent process id], termination status, user's ID, owner's ID...)*

A process is executed on the computer's central processing unit (**CPU**) as machine code during the runtime phase of a computer program's life cycle.

A process logically is divided into segments:
**Text:** The instructions of the programs.
**Data:** Static variables used by the program.
**Heap:** Area from which the program dynamically allocates extra memory.
**Stack:** A piece of memory that grows and shrinks as functions are called and return…

![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/b3dd6a31-aea8-4120-ad04-f590c5777170/75edff35-9a78-4434-bc06-6cf7b9882f43/Untitled.png)

A process can create another process using the `fork()` system call.
The process that calls `fork()` called the **Parent Process**, and the new process called the **Child Process**.

![shape_lQRZC_4bRBmmZGC_we8hf at 24-03-08 18.42.45.png](https://prod-files-secure.s3.us-west-2.amazonaws.com/b3dd6a31-aea8-4120-ad04-f590c5777170/c5f578b1-8854-4dfd-b3a5-9e3a6ffc4960/shape_lQRZC_4bRBmmZGC_we8hf_at_24-03-08_18.42.45.png)

When the `fork()` system call is called the **Kernel** creates a duplicate of the process (**Parent Process**), the child process inherits copies of the parent’s data, stack and heap’s segments.

### The “init” Process

When booting the system, the **Kernel** creates a special process called **“init”** the **Parent of All Processes** derived from `/sbin/init` the PID of **init** is `1` & runs with the *sudo* privileges.
**”init”** can’t be killed even using *sudo*. The main task of this process is to create and monitor a range of processes required by a running system.

---

### System Calls

A system call is controlled entry point into the **Kernel** allowing a process to request from the **Kernel** to perform some actions on the process’s behalf.

A system call changes the state from **USER Mode** to **KERNEL Mode**, so that the CPU can access protected **Kernel** memory.
Each system call is identified by a unique number *(the identifier is not visible to programs).*

Example: [Linux Syscall Table](https://filippo.io/linux-syscall-table/)

| %eax %rax | System call | %rdi | %rsi | %rdx | %r10 | %r8 | %r9 |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | sys_read | unsigned int fd | char *buf | size_t count |  |  |  |
| 1 | sys_write | unsigned int fd | const char *buf | size_t count |  |  |  |
| 2 | sys_open | const char *filename | int flags | int mode |  |  |  |
| 3 | sys_close | unsigned int fd |  |  |  |  |  |
| 9 | sys_mmap | unsigned long addr | unsigned long len | unsigned long prot | unsigned long flags | unsigned long fd | unsigned long off |

Each system call has a set of arguments that specify information to be transformed from **User space** to **Kernel space** and vise-versa.

---

### The Steps of invoking a System Call on a specific hardware x86_32

**Step1
→** The application program makes a system call by invoking a wrapper function in the C library.

<aside>
💡 When an application program needs to perform an operation that requires interaction with the OS (a system call), it invokes a function from C library **(Wrapper function)** that in turn makes the actual system call.

</aside>

**Step2
→** The **Wrapper function** must make all the arguments available to the system call **Trap handling routine**. These arguments are passed to the **wrapper** via the **stack**, but the kernel expect them in a **specific registers**. The **Wrapper function** copies these arguments to these registers. **[it takes the arguments from the stack & place them into specific registers]**

<aside>
💡 For example, using the **read system call
→ %eax** register holds the identifier of the system call
**→ %rdi** holds the **file descriptor
→ %rsi** holds the address of the buffer
**→ %rdx** hold the length of the line to be read.

</aside>

**Step3
→** Since all the syscalls enters the **Kernel** in the same way. The **Kernel** needs to identify the syscall used by some method. To permit this, the **Wrapper function** copies the syscall identifier into a specific CPU Register (**%eax**).

**Step4
→** The **Wrapper function** execute a **trap machine instruction** `int 0x80;` which causes the preprocessor to switch from **USER Mode** to **KERNEL Mode** and execute code pointed to by location `0x80` of the system’s trap vector.

```nasm
/* x86_32 */
_start: 
	mov eax, 1;      // sysc number for exit
	xar ebx, ebx;    // exit code 0
	int 0x80;        // Make the syscall
```

**Step5
→** In response to the trap to location `0x80`; The **Kernel** invokes its syscall() routine to handle this trap. This handler:
1> Saves register values onto the **Kernel Stack**
2> Checks the validity of the syscall number
3> Invokes the syscall service routine which found by using the syscall identifier to index a table of all syscall service routines [ The syscall number is often used as index into a table of syscalls service routines. This table is often referred to **sys_call_table** in the **Kernel**. Each entry in the table corresponds to a specific syscall and points to the corresponding service routine ]
If the syscall service routine has any arguments, it first check their validity, for example it checks that addresses point to valid locations in user memory. Then the service routine perform the required task, which may involve modifying values at addresses specified in the given arguments and transferring data between **User** memory and **Kernel** memory. Finally, the service routine returns a result status to the system_call() routine.
4> Restores register values from the **Kernel Stack** and places the syscall return value on the stack.
5> Returns to the **Wrapper function**, simultaneously returning the process to **User Mode**.

**Step6
→** If the return value of syscall service routine indicated an `error`, the **Wrapper function** sets the global variable **‘errno’** using this value.
The **Wrapper function** then returns to the caller, providing an integer return value indicating the success or failure of the syscall.

---

![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/b3dd6a31-aea8-4120-ad04-f590c5777170/5c47a906-acf6-46d2-b16d-89f531c4d30e/Untitled.png)

### Memory layout of a process

**Text Segment**

Contains machine language instructions of the program run by the process. The text segment is READ-ONLY so that it doesn’t accidentally modify its own instructions via a bad pointer value.

**Initialized Data Segment**

Contains `global` & `static` variables that explicitly initialized, it also contains the `const` variables. *[This segment could be classified into initialized read-only area and the initialized read-write area, since could be a `const` global variable]*

**Uninitialized Data Segment**

Contains `global` & `static` variables that are not initialized. The system initializes all memory segment to zero.

**Stack**

Dynamically growing and shrinking segment containing stack frames. [ one stack frame is allocated for each currently called function ]

On most Linux and Unix implementation: The stack resides at high end of memory and grows downward *(toward the heap).* A special-purpose register, the stack pointer tracks the current top of the stack

![shape_sbQ6SKgowjinN7RgDQNym at 24-03-09 03.02.18.png](https://prod-files-secure.s3.us-west-2.amazonaws.com/b3dd6a31-aea8-4120-ad04-f590c5777170/c554d17e-6012-4e73-b588-a0017f590aa4/shape_sbQ6SKgowjinN7RgDQNym_at_24-03-09_03.02.18.png)

**Heap**

An area from which memory can be dynamically allocated at run time.

### Program Counter

A program counter is a specific register that stores the memory address of the next instruction to be executed in a program, it keeps track of the current position in the program’s execution and is used by the processor to fetch the next instruction to be executed.
