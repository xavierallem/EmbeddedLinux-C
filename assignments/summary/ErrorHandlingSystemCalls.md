# System Call Error Handling Summary

Linux provides system calls that are the basic functions that help do stuff
in Linux. 
Hence it becomes necessary to understand them and always use them correctly.

![error](assignments/summary/Assets/slide13.jpg)

## Code Snippets

- [**Print Error Messages Function**](#print-error-messages-function)
- [**Linux I/O routines**] (#2)
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