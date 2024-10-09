/* OS system calls */
#ifndef __SYSCALL_H__
#define __SYSCALL_H__
#include <lfs.h>
#include <lfs_util.h>

extern int __syscall(int a,...);
enum {
OS_NULLPROCESS = 0,
OS_PUTC ,
OS_PUTS ,
OS_GETC,
OS_GETS,
OS_CLOSE,  /* Devices */
OS_OPEN ,
OS_READ ,
OS_WRITE ,
OS_CREATE , /* Processes */ 
OS_KILL, /* Exit */
OS_READY ,
OS_SLEEP ,
OS_FREE ,
OS_MALLOC, 
OS_GETDEV ,
OS_SEMA_INIT,  /* Semapho3 */
OS_SEMA_SIGNAL, 
OS_SEMA_WAIT ,
OS_PIN_MODE ,
OS_PIN_SET ,
OS_PIN_GET ,
OS_FREE_HEAP, 
OS_GETPID ,
OS_EXIST ,
OS_FS_INIT ,
OS_ATTACH_MEDIA, 
OS_ATTACH_LOCKS , //OS_LIST_DIR 25
OS_FOPEN,
OS_FSEEK,
OS_FREAD,
OS_FWRITE,
OS_FCLOSE,
OS_FTELL,
OS_FREWIN,
OS_TRUNCATE,
OS_SIZE,
OS_AVAILABLE,
OS_MKDIR,
OS_FEOF,

OS_OPENDIR,
OS_READDIR,

OS_REMOVE,
OS_RENAME,
OS_FORMAT,
OS_MOUNT,
OS_UNMOUNT,
OS_DISK_FREE,

OS_CLOSEDIR,
OS_CREATEDIRECTORY,
OS_IS_DIR,
OS_FFLUSH,
OS_FGETC,
OS_FGETCS,
OS_FPUTC,
OS_FPUTCS,
OS_FGETPOS,
OS_NUM_TASK ,
OS_STRUCT_TASK, 
OS_LOAD_ELF,
OS_HEAP_FREE,
OS_YIELD,
OS_GLOBAL_PATH,
OS_UPDATE_PATH,
OS_GET_PATH,
OS_CD,
OS_JSON,
OS_GET_LEN,


};



typedef struct syscall_s
{
	void *(*open)(const char *path, int flags);
	int (*write)(void *pbuf, int size, void *file);
    int (*read)(void *pbuf, int size, void *file);
    int (*close)(void *file);
    int (*seek)(void *file, int offset, int whence);
    int (*tell)(void *file);
    int (*rewind)(void *file);
    int (*truncate)(int size, void *file);
    int (*size)(void *file);
    int (*available)(void *file);

    int (*mkdir)(const char *path);
    void *(*openDir)(const char *path);
    int (*closeDir)(void *dir);
    int (*readDir)(void *dir, void *info);
    int (*rewindDir)(void *dir);
    int (*tellDir)(void *dir);
    int (*seekDir)(void *dir, int offset);


    int (*format)(void *_lfs, void *_cfg);
    int (*mount)(void *_lfs, void *_cfg);
    int (*unmount)(void *_lfs);
    int (*remove)(const char *path);
    int (*rename)(const char *oldpath, const char *newpath);
    int (*disk_free)(void);
    int (*tree)(const char *dir_path, char *pbuf, int buf_size);
    
    int (*exist)(const char *path);

    void (*sleep)(uint32);
    void (*kill)(int);
    int (*getpid)();
    void (*yield)();
    void (*ready)(int);
    //int (*create)(void *procaddr, uint32 ssize, int priority,const char *name, int nargs, ...);
    void (*reset)();//SYSCON = 0x5555; 
    void (*putc)(int ,char );
    void (*puts)(int ,char *,int);
    int (*kbhit)();
    int (*readbyte)();
    char *(*full_path)(char *);
    void (*updatepath)();
    void *(*malloc)(uint32);
    void (*free)(void *);
    void *(*self)(int);
    char *(*getpath)();
    void (*cd)(char *);
    uint32 (*freeHeap)();
    uint32 (*elf_execve)(const char *file, void *res);
    int (*create)(void *procaddr, uint32 ssize, int priority,const char *name);
    void *(*js0n)(void *);////const char *(*js0n)(const char *key, size_t klen,const char *json, size_t jlen, size_t *vlen);
    uint32 (*len)();
    char *(*fifo)();
}syscall_t;
extern syscall_t *sys;
extern syscall_t syscallp;



extern int syscall_os_init(syscall_t *sys_obj);

#endif

