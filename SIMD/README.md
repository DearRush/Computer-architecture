# Lab:SIMD 

## Main Purpose:

To understand and master the basic usage of the Intel SIMD command.

## Summarize

SIMD (Single Instruction Multiple Data) that is, Single Instruction Stream Multiple Data Stream, is a kind of controller to control multiple processors, at the same time on a set of data (also known as the "data vector") in each of the same operation to realize the spatial parallelism of the technology. The technology. This simply means that a single instruction can process more than one piece of data at the same time.

The goal of this experiment is to improve program performance by implementing SIMD through the use of loop unrolling and specialized Intel SIMD intrinsics functions. In the assignment, this metric is measured by the statistics of the program's runtime.

In the programs sum.c and sum_256.c, I used the techniques of loop expansion, 128-bit dedicated computational functions, and 256-bit dedicated computational functions, respectively, and finally succeeded in making the program runtime significantly reduced.

The output of the sum.c program is:

```
naive: 16.16 microseconds
unrolled: 15.10 microseconds
vectorized: 12.32 microseconds
vectorized unrolled: 11.92 microseconds
```

The output of the sum256.c program is:

```
naive: 16.30 microseconds
unrolled: 15.10 microseconds
vectorized: 11.92 microseconds
vectorized unrolled: ERROR!(Functions not written)
```

From the appeal results, it can be found that the code using SIMD instruction runs significantly faster than the normal code.
Therefore, I believe that by increasing the number of parallel bytes, the program is able to process more data at the same time, which is the reason for the phenomenon. Appropriate use of hardware parallelism in programming can better improve program performance.





