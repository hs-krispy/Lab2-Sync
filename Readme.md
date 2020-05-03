# **Concurrent Binary Search Tree** 

<img src="https://img.shields.io/github/issues/hs-krispy/Lab2_Sync"> <img src="https://img.shields.io/github/forks/hs-krispy/Lab2_Sync"> <img src="https://img.shields.io/github/stars/hs-krispy/Lab2_Sync"> <img src="https://img.shields.io/github/last-commit/hs-krispy/Lab2_Sync"> <img src="https://img.shields.io/github/repo-size/hs-krispy/Lab2_Sync"> [![HitCount](http://hits.dwyl.com/hs-krispy/Lab2-Sync.svg)](http://hits.dwyl.com/hs-krispy/Lab2-Sync)

## Team

|        [leeshinyook](https://github.com/leeshinyook)         |          [hs-krispy](https://github.com/hs-krispy)           |
| :----------------------------------------------------------: | :----------------------------------------------------------: |
| <img src="https://avatars3.githubusercontent.com/u/55838461?s=400&u=06a56002fd08e659a979557ea8d8a79efe9ba1ec&v=4" width="50%" align="center"> | <img align="center" src="https://avatars0.githubusercontent.com/u/58063806?s=400&v=4" width="50%"> |

We are students of Dankook University's software department. We are working on a project for the Cpu 

scheduling algorithm.

**Pull requests are always welcome.**

## Code Structure

We did this project to measure the performance of both locking(`fine-grained lock`, `coarse-grained lock`) in BST.

1. `insert`, `remove`

Basic BST in single thread

2. `insert_fg`, `remove_fg`

Fine-grained lock in multi-threaded BST

3. `insert_cg`, `remove_cg`

Coarse-grained lock in multi-threaded BST



## How to run

We have set up a makefile for convenient code execution.

Since it is a file written in c lang, so `gcc` installation is required!

Also, `make` installation is required, so please install it first.

### 1. Clone Project

~~~
$ git clone https://github.com/hs-krispy/Lab2_Sync.git
~~~

### 2. Make 

~~~
$ make lab2_bst
~~~

The make command creates an executable file.
An executable file should have been created in your current directory.

### 3. Run

~~~
$ ./lab2_bst -t 4 -c 1000000
~~~

If you want to delete the generated files, type  `make clean`



## Measure and Review

We visualized about 30 data per thread Using Python. First, using c file input and output, csv files were created. The set of data is in BST.csv. 



### Insert

![스크린샷 2020-05-04 오전 2 55 51](https://user-images.githubusercontent.com/55838461/80921682-c78fb300-8db2-11ea-9eb2-16bb06a3e436.png)

That is, even though the number of threads increases, there is no part to be processed in parallel, and the above results can be confirmed due to the number of locks and unlocks and the cost issues associated with context switching.



### Delete

![스크린샷 2020-05-04 오전 2 50 14](https://user-images.githubusercontent.com/55838461/80921545-03764880-8db2-11ea-9e7b-a330599b1b8b.png)



The lock contention of threads occurs excessively and the execution time is slowed down due to the cost.
As a result, it can be seen that in a multi-threaded environment, lock and unlock must be properly applied around the critical area to improve performance.

