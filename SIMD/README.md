#### 实验： SIMD 

#### 指令目的： 了解并掌握 Intel SIMD 指令的基本用法



#### 总结

SIMD(**Single Instruction Multiple Data**)即单指令流多数据流，是一种采用一个控制器来控制多个处理器，同时对一组数据（又称“数据向量”）中的每一个分别执行相同的操作从而实现空间上的并行性的技术。简单来说就是一个指令能够同时处理多个数据。

而这个实验的目的正是通过使用循环展开和专用的Intel SIMD intrinsics 函数等实现SIMD，进而实现程序性能的提升。在作业中，这一指标主要是通过程序运行时间的统计而进行测量的。

在程序sum.c,sum_256.c中我分别使用了循环展开，128位的专用计算函数，256位的专用计算函数等技巧，最终成功使得程序运行时间显著降低。

sum.c程序输出为：

```
naive: 16.16 microseconds
unrolled: 15.10 microseconds
vectorized: 12.32 microseconds
vectorized unrolled: 11.92 microseconds
```

sum_256.c程序输出是：

```
naive: 16.30 microseconds
unrolled: 15.10 microseconds
vectorized: 11.92 microseconds
vectorized unrolled: ERROR!(未编写函数)
```







