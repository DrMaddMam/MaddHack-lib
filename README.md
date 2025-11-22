## Maddhack LIB
This is a general and specialized C library that includes:  
  * A 128 bit parser  
  * A fast memory library  
  * A simple flags system  
  * And generic C hackery macros!  

Made by Fanta AKA DrMaddMam
## Documentation
# MaddHack Initizalizers/Cleanup
Two functions that should be run on the start and end of a program, they initalize flags and reset the memory library  
```initMaddHack```
-- Returns if all init functions were successful  
```exitMaddHack```
-- Returns the amount of errors detected in your code (Ex. Unfreed memory)  
# Fast Memory Library
My fast memory library is a DOOM-like memory library that has a set arrary in memory on startup that you can allocate (getMem) and mark as unused (freeMem)  
```
int main(int argc, char** argv) {
    if (!initMaddHack()) {
        return -1;
    }
    struct mem_part* p1 = getMem(100);
    if (!p1) {
        return -2;
    } else if (*(char**)p1) {
        return -3;
    }
    strcpy(*(char**)p1, "Hello, MaddHack!");
    printf("%s\m", *(char**)p1);
    freeMem(p1);
}
```
You might look at this code and think it is insane but it is actually a very simple way to use the code;  
If you want to ~~be~~ act professional you can use
```
int main(int argc, char** argv) {
    if (!initMaddHack()) {
        return -1;
    }
    struct mem_part* p1 = getMem(100);
    if (!p1) {
        return -2;
    } else if (p1->location) {
        return -3;
    }
    strcpy(p1->location, "Hello, MaddHack!");
    printf("%s\m", p1->location);
    freeMem(p1);
    exitMaddHack()
}
```
# 128 Bit parser
It is a quartet of functions related to 128 bit integers  
```str_to_u128```
-- Converts a string to a U128 integer  
-- Arg 1: const char* s (string pointer)  
-- Arg 2: UMin Base (the base for the number, 10/16)  
```str_to_i128```
-- Converts a string to a I128 integer  
-- Arg 1: const char* s (string pointer)  
-- Arg 2: UMin Base (the base for the number, 10/16)  
```print_u128```
-- Prints a U128 to a buff
-- Arg 1: U128 n (the specifed number)  
-- Arg 2: U8* buf (the buffer to print to)  
-- Arg 3: UMin bufsize (the size of the buffer)
```print_i128```
-- Prints a I128 to a buff
-- Arg 1: I128 n (the specifed number)  
-- Arg 2: U8* buf (the buffer to print to)  
-- Arg 3: UMin bufsize (the size of the buffer)
# Flags
It is a flag system to efficiently use an integer to store {bit count} flags
```setFlag```
-- Sets a flag in the specified number pointer
-- Arg 1: UMax flag (the flag to be set)  
-- Arg 2: UMax *ptr (the number to have that flag set)  
-- Returns if it was successful  
```getFlag```
-- Gets a flag in the specifed number pointer  
-- Arg 1: UMax flag (the flag to test for)  
-- Arg 2: UMax *ptr (the number to have that flag tested for)  
-- Returns if the flag was detected or if the pointer was null  
```clearFlag```
-- Clears the specified flag in the number pointer  
-- Arg 1: UMax flag (the flag to clear)  
-- Arg 2: UMax *ptr (the number to have the flag cleared)  
-- Returns if the flag was cleared or if the number was not null  
