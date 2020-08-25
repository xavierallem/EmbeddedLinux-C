# Common Programming Errors Summary

![error](assignments/summary/Assets/Errors-In-C.png)

## Common Mistakes while C Programming

- ### Dereferencing Bad Pointers 

A common example of dereferencing a bad pointer is:
Suppose we want to use scanf to read an integer from stdin into a variable. 
The correct way to do this is to pass scanf a format string and the address of the
variable.


**Wrong way**
```c
scanf("%d", val)
```

**Right way**
```c
scanf("%d",&val)
```

- ### Reading Uninitialized Memory

If variables are initialized, we cannot assume them to be zero.

For eg.

**Wrong way**
```c
/* Return y = Ax */
void matvec(int **A, int *x, int n)
{
    int i, j;
    int *y = (int *)Malloc(n * sizeof(int));
    for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
    y[i] += A[i][j] * x[j];
    return;
}

```
**Right way**
```c
/* Return y = Ax */
void matvec(int **A, int *x, int n)
{
    int i, j;
    int *y = (int *)calloc(n * sizeof(int));
    for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
    y[i] += A[i][j] * x[j];
    return;
}

```

- ### Assuming that Pointers and the Objects They Point to Are the Same Size

One common mistake is to assume that pointers to objects are the same size as
the objects they point to.

For eg. for length of string

**Wrong way**
```c
/* Create an nxm array */
int size_of_array (char *array)
{
    return sizeof(array);
}

```
**Right way**
```c
/* Create an nxm array */
int size_of_array (char *array)
{
    return strlen(array);
}

```

- ### Making Off-by-One Errors

Off-by-one errors are another common source of overwriting bugs.

```c
/* Create an nxm array */
char *makeArray2(int n, int m)
{
    int i;
    char buf[64];
    for (i = 0; i <= n; i++)
        buf[i] = i;
    return buf;
}

```
Here we are  initializing n+1 elements which is wrong.

- ### Referencing a Pointer Instead of the Object It Points to

If we are not careful about the precedence and associativity of C operators, then
we incorrectly manipulate a pointer instead of the object it points to.

For eg.

```c
int *binheapDelete(int **binheap, int *size)
{
    int *packet = binheap[0];
    binheap[0] = binheap[*size - 1];
    
    *size--; /* This should be (*size)-- */
    heapify(binheap, *size, 0);
    return(packet);
}

```

The unary -- and * operators have the same precedence and
associate from right to left, the code in line 6 actually decrements the pointer
itself instead of the integer value that it points to. Hence to avoid it we use "()"

- ### Misunderstanding Pointer Arithmetic

Another common mistake is to forget that arithmetic operations on pointers are
performed in units that are the size of the objects they point to , which are not
necessarily bytes. (i.e pointer++ will increment to the next unit not the next byte)
For eg.

```c
int *search(int *p, int val)
{
    while (*p && *p != val)
    p += sizeof(int); /* Should be p++ */
    return p;
}

```
Because integer is 4 bytes hence it will increment 4 bytes instead of per unit

- ### Referencing Nonexistent Variables

This function returns a pointer (say, p) to a local variable on the stack and then
pops its stack frame.
Although p still points to a valid memory address, it no longer
points to a valid variable. When other functions are called later in the program, the
memory will be reused for their stack frames.
Later, if the program assigns some value to *p, then it might actually be modifying an entry in another function’s stack frame, with potentially disastrous.

```c
int *stackref ()
{
    int val;
    return &val;
}

```

- ### Introducing Memory Leaks

Memory leaks occur when programmers create variables or pointers in the heap memory and forget to free allocated blocks.

```c
oid leak(int n)
{
    FILE *fp;
    fp = fopen("file.txt", "w");

    return;
/* fp is garbage at this point */
}

```
