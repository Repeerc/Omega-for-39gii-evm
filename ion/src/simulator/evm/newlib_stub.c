#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/times.h>

#include "sys_llapi.h"

#ifdef __cplusplus
    extern "C" {
#endif

#undef errno
extern int errno;

#define HEAP_END    0x023F4000


extern unsigned int __HEAP_START;
static void *heap = NULL;

//void __sync_synchronize()  __attribute__((naked));
void __sync_synchronize()
{
    //asm volatile("" : : : "memory");
}


caddr_t _sbrk ( uint32_t incr )
{

    
	void *prev_heap;
    if(heap == NULL){
        heap = (uint32_t *)&__HEAP_START;
    }
    //ll_putStr("_sbrk\n");

    prev_heap = heap;
    
    if(((uint32_t)heap + incr) > HEAP_END){
        //dbg_printf("MEMORY OVER FLOW\n");
        ll_putStr("Mem OF.....\n");

        return 0;
    }
    heap += incr;
    //dbg_printf("heap:%x, incr:%d\n", heap, incr);
    return (caddr_t)prev_heap;

}

size_t xPortGetFreeHeapSize( void )
{
	return HEAP_END - (uint32_t)heap;
}

size_t xPortGetTotalHeapSize( void )
{
	return HEAP_END - (uint32_t)(&__HEAP_START);
}

uint32_t getHeapAddr()
{
    return (uint32_t)heap;
}

int _close_r(struct _reent *pReent, int fd) {
    pReent->_errno = ENOTSUP;
    return -1;
}

int _execve_r(struct _reent *pReent, const char *filename, char *const *argv, char *const *envp) {
    pReent->_errno = ENOTSUP;
    return -1;
}

int _fcntl_r(struct _reent *pReent, int fd, int cmd, int arg) {
    pReent->_errno = ENOTSUP;
    return -1;
}

int _fork_r(struct _reent *pReent) {
    pReent->_errno = ENOTSUP;
    return -1;
}

int _fstat_r(struct _reent *pReent, int file, struct stat *st) {
    pReent->_errno = ENOTSUP;
    return -1;
}

int _getpid_r(struct _reent *pReent) {
    pReent->_errno = ENOTSUP;
    return -1;
}

int _isatty_r(struct _reent *pReent, int file) {
    pReent->_errno = ENOTSUP;
    return -1;
}

int _isatty(int file)
{
    return -1;
}

int _kill_r(struct _reent *pReent, int pid, int signal) {
    pReent->_errno = ENOTSUP;
    return -1;
}

int _link_r(struct _reent *pReent, const char *oldfile, const char *newfile) {
    pReent->_errno = ENOTSUP;
    return -1;
}

_off_t _lseek_r(struct _reent *pReent, int file, _off_t offset, int whence) {
    pReent->_errno = ENOTSUP;
    return -1;
}

int _mkdir_r(struct _reent *pReent, const char *pathname, int mode) {
    pReent->_errno = ENOTSUP;
    printf("_mkdir_r\n");
    return -1;
}

int _open_r(struct _reent *pReent, const char *file, int flags, int mode) {
    pReent->_errno = ENOTSUP;
    printf("_open_r\n");
    return -1;
}

_ssize_t _read_r(struct _reent *pReent, int fd, void *ptr, size_t len) {
    pReent->_errno = ENOTSUP;
    printf("_read_r\n");
    return -1;
}

_ssize_t _rename_r(struct _reent *pReent, const char *oldname, const char *newname) {
    pReent->_errno = ENOTSUP;
    return -1;
}


int _stat_r(struct _reent *pReent, const char *__restrict __path, struct stat *__restrict __sbuf )
{
    pReent->_errno = ENOTSUP;
    return -1;
}

_CLOCK_T_ _times_r(struct _reent *pReent, struct tms *tbuf) {
    pReent->_errno = ENOTSUP;
    //ll_putStr("GET TIME\n");
    return -1;
}

int _unlink_r(struct _reent *pReent, const char *filename) {
    pReent->_errno = ENOTSUP;
    return -1;
}

int _wait_r(struct _reent *pReent, int *wstat) {
    pReent->_errno = ENOTSUP;
    return -1;
}

_ssize_t _write_r(struct _reent *pReent, int fd, const void *buf, size_t nbytes) {

    int i;
    const char *ch = buf;
/*
    if(muxWrite == NULL)
    {
        muxWrite = xSemaphoreCreateMutex();
    }
*/
	if(fd < 3){

       // xSemaphoreTake(muxWrite, portMAX_DELAY);
        pReent->_errno = 0;
        
        //for(int i = 0; i< nbytes; i++)
        //{
        //    debugPutch( ch[i] );
        //}

        ll_putStr2((char *)buf, nbytes);
        
        return nbytes;
       // xSemaphoreGive(muxWrite);

    }
    return -1;
}


struct timeval {
        long    tv_sec;         /* seconds */
        long    tv_usec;        /* and microseconds */
};

int _gettimeofday_r(struct _reent *pReent, struct timeval *__tp, struct timezone *__tzp) {
    //pReent->_errno = ENOTSUP;
    pReent->_errno = 0;

    if(__tp != NULL)
    {
        __tp->tv_sec = ll_gettime_us()/1000000;
        __tp->tv_usec = ll_gettime_us();
    }else{
        printf("__tp NULL\n");
    }

    if(__tzp != NULL)
    {
        //__tzp->tz_minuteswest = 0;
        //__tzp->tz_dsttime = 0;
    }else{
        //printf("__tzp NULL\n");
    }


    
    //printf("GET _gettimeofday_r\n");
    
    return -1;
}

/*
 * write "len" of char from "ptr" to file id "fd"
 * Return number of char written.
 *
* Only work for STDOUT, STDIN, and STDERR
 */
/*
char kmsgBuff[4096];
unsigned int kmsgBuff_ptr = 0;

int _write(int fd, char *ptr, int len) {
    
	//asm volatile ("ldr r0,%0" :: "m"(fd));
	//asm volatile ("ldr r1,%0" :: "m"(ptr));
	//asm volatile ("ldr r2,%0" :: "m"(len));
	//asm volatile ("swi #1000");
	

    int i = 0;

    if (fd > 2) {
        return -1;
    }

    while (*ptr && (i < len)) {
        kmsgBuff[kmsgBuff_ptr++] = *ptr;
        if (kmsgBuff_ptr > 4096) {
            kmsgBuff_ptr = 0;
        }
        uartdbg_putc(*ptr);
        //console_puts(*ptr);

        i++;
        ptr++;
    }

    return i;
}
*/

int fsync(int __fd) {
    
    return 0;
}

char *getcwd(char *buf, size_t size) {

    return NULL;
}

void abort(void) {
    //Abort called
    printf("abort\n");
    while (1)
        ;
}

void _exit(int i) {
    printf("_exit\n");
    while (1)
        ;
}

#ifdef __cplusplus          
    }         
#endif