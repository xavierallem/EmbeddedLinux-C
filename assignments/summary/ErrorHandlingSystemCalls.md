# System Call Error Handling Summary

Linux provides system calls that are the basic functions that help do stuff
in Linux. 
Hence it becomes necessary to understand them and always use them correctly.

![error](assignments/summary/Assets/slide13.jpg)

## Code Snippets

- [**Print Error Messages Function**](#print-error-messages-function)
- [**Linux I/O routines**](#linux-i/o-routines)
- [**Standard File I/O functions**] (#3)
- [**Dynamic Storage**] (#4)
- [**Process Control**] (#5)
- [**Signal Functions**] (#6)
- [**Memory Mapping**] (#7)
- [**Socket Functions**] (#8)
- [**DNS functions**] (#9)
- [**Pthread functions**] (#10)
- [**Semaphores**] (#11)
- [**Other Uncommon functions**] (#12)

### Print Error Messages Function

```c
/************************** 
 * Error-handling functions
 **************************/
/* $begin errorfuns */
/* $begin unixerror */
void unix_error(char *msg) /* unix-style error */
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(0);
}
/* $end unixerror */

void posix_error(int code, char *msg) /* posix-style error */
{
    fprintf(stderr, "%s: %s\n", msg, strerror(code));
    exit(0);
}

void dns_error(char *msg) /* dns-style error */
{
    fprintf(stderr, "%s: DNS error %d\n", msg, h_errno);
    exit(0);
}

void app_error(char *msg) /* application error */
{
    fprintf(stderr, "%s\n", msg);
    exit(0);
}
/* $end errorfuns */

```

### Linux I/O routines

```c
/********************************
 * Wrappers for Unix I/O routines
 ********************************/

int Open(const char *pathname, int flags, mode_t mode) 
{
    int rc;

    if ((rc = open(pathname, flags, mode))  < 0)
    unix_error((char*)"Open error");
    return rc;
}

ssize_t Read(int fd, void *buf, size_t count) 
{
    ssize_t rc;

    if ((rc = read(fd, buf, count)) < 0) 
    unix_error((char*)"Read error");
    return rc;
}

ssize_t Write(int fd, const void *buf, size_t count) 
{
    ssize_t rc;

    if ((rc = write(fd, buf, count)) < 0)
    unix_error((char*)"Write error");
    return rc;
}

off_t Lseek(int fildes, off_t offset, int whence) 
{
    off_t rc;

    if ((rc = lseek(fildes, offset, whence)) < 0)
    unix_error((char*)"Lseek error");
    return rc;
}

void Close(int fd) 
{
    int rc;

    if ((rc = close(fd)) < 0)
    unix_error((char*)"Close error");
}

int Select(int  n, fd_set *readfds, fd_set *writefds,
       fd_set *exceptfds, struct timeval *timeout) 
{
    int rc;

    if ((rc = select(n, readfds, writefds, exceptfds, timeout)) < 0)
    unix_error((char*)"Select error");
    return rc;
}

int Dup2(int fd1, int fd2) 
{
    int rc;

    if ((rc = dup2(fd1, fd2)) < 0)
    unix_error((char*)"Dup2 error");
    return rc;
}

void Stat(const char *filename, struct stat *buf) 
{
    if (stat(filename, buf) < 0)
    unix_error((char*)"Stat error");
}

void Fstat(int fd, struct stat *buf) 
{
    if (fstat(fd, buf) < 0)
    unix_error((char*)"Fstat error");
}

```