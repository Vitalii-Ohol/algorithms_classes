Some little scripts from algorithms classes. The year 2018.  
All scripts were used in [SPOX](http://spox.spoj.pl/) system and have very little with readability and more with program speed.  
It means:
  * minimal use of functions, as functions loads to stack and that takes our precious time
  * usage of pre-increment and pre-decrement, as it takes 2 assembler commands instead of 3
  * decrement usage inside loops, as compiler optimized for this case
  * usage of fixed size types (ex `uint_fast16_t`) instead of regular types (ex. `unsigned int`)
  * usage of keyword `register`
  * `getc_unlocked` reading and `putchar_unlocked` writing
  * usage of bit operators instead of readable/normal calculations
  * abnormal usage of pointers and references

These techniques are **useless** in real-life programming but allowed to reduce execution time from 1-5 seconds to 0.01-0.03 seconds in SPOX system
