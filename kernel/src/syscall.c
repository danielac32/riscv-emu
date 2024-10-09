#include <stdint.h>
#include <syscall.h>
#include <elf.h>
#include <littlefs.h>
#include <exception.h>
#include <process.h>

syscall_t *sys;

void* sys_open(const char *path, int flags){
    return (void *)__syscall(OS_FOPEN,path,flags);
}
int sys_exist(const char *path){
    return __syscall(OS_EXIST,path);
}
int sys_write(void *pbuf, int size, void *file){
    return __syscall(OS_FWRITE,pbuf,size,file);
}
int sys_read(void *pbuf, int size, void *file){
    return __syscall(OS_FREAD,pbuf,size,file);
}
int sys_close(void *file){
    return __syscall(OS_FCLOSE,file);
}
int sys_seek(void *file, int offset, int whence){
    return __syscall(OS_FSEEK,file,offset,whence);
}
int sys_tell(void *file){
    return __syscall(OS_FTELL,file);
}
int sys_rewind(void *file){
    return __syscall(OS_FREWIN,file);
}
int sys_truncate(int size, void *file){
    return __syscall(OS_TRUNCATE,size,file);
}
int sys_size(void *file){
    return __syscall(OS_SIZE,file);
}
int sys_available(void *file){
    return __syscall(OS_AVAILABLE,file);
}

int sys_mkdir(const char *path){
    return __syscall(OS_MKDIR,path);
}
void *sys_openDir(const char *path){
    return (void *)__syscall(OS_OPENDIR,path);
}
int sys_closeDir(void *dir){
    return __syscall(OS_CLOSEDIR,dir);
}
int sys_readDir(void *dir, void *info){
    return __syscall(OS_READDIR,dir,info);
}
int sys_rewindDir(void *dir){
    return 0;
}
int sys_tellDir(void *dir){
    return 0;
}
int sys_seekDir(void *dir, int offset){
    return 0;
}

int sys_format(void *_lfs, void *_cfg){
    return __syscall(OS_FORMAT,_lfs,_cfg);
}
int sys_mount(void *_lfs, void *_cfg){
    return __syscall(OS_MOUNT,_lfs,_cfg);
}
int sys_unmount(void *_lfs){
    return __syscall(OS_UNMOUNT,_lfs);
}
int sys_remove(const char *path){
    return __syscall(OS_REMOVE,path);
}
int sys_rename(const char *oldpath, const char *newpath){
    return __syscall(OS_RENAME,oldpath,newpath);
}
int sys_free(void){
    return __syscall(OS_DISK_FREE);
}
void sys_sleep(uint32 ticks){
    __syscall(OS_SLEEP,ticks);
}

void sys_kill(int pid){
    __syscall(OS_KILL,pid);
}

int sys_getpid(){
    return __syscall(OS_GETPID);
}

void sys_yield(){
    __syscall(OS_YIELD);
}

void sys_ready(int pid){
    __syscall(OS_READY,pid);
}

char *sys_full_path(char *s){
    return (char *)__syscall(OS_GLOBAL_PATH,s);
}
void sys_update_path(){
    __syscall(OS_UPDATE_PATH);
}

void *sys_malloc(uint32 size){
    return (void *)__syscall(OS_MALLOC,size);
}

void sys_mfree(void *p){
     __syscall(OS_FREE,p);
}

void sys_putc(int t,char c){
    __syscall(OS_PUTC,t,c);
}
void sys_puts(int a ,char *s,int r){
    __syscall(OS_PUTS,a,s,r);
}

void *sys_struct_task(int pid){
return (void *)__syscall(OS_STRUCT_TASK,pid);
}

char *sys_get_path(){
    return (char *)__syscall(OS_GET_PATH);
}

void sys_cd(char *s){
    __syscall(OS_CD,s);
}

uint32 sys_elf_execve(const char *file, void *res){
       return __syscall(OS_LOAD_ELF,file,res);
}

int sys_create(void *procaddr, uint32 ssize, int priority,const char *name){
    return __syscall(OS_CREATE,procaddr,ssize,name);
}

const char *sys_js0n(const char *key, size_t klen,const char *json, size_t jlen, size_t *vlen){
    return (char *)__syscall(OS_JSON,key,klen,json,jlen,vlen);
}

uint32 sys_free_heap(){
    return __syscall(OS_FREE_HEAP);
}


struct irq_context *do_syscall(struct irq_context *ctx);

int syscall_os_init(syscall_t *sys_obj){

    sys = sys_obj;
    sys->exist = sys_exist;
    sys->open = sys_open;
    sys->write = sys_write;
    sys->read = sys_read;
    sys->close = sys_close;
    sys->seek = sys_seek;
    sys->tell = sys_tell;
    sys->rewind = sys_rewind;
    sys->truncate = sys_truncate;
    sys->size = sys_size;
    sys->available = sys_available;

    sys->mkdir = sys_mkdir;
    sys->openDir = sys_openDir;
    sys->closeDir = sys_closeDir;
    sys->readDir = sys_readDir;
    sys->rewindDir = sys_rewindDir;
    sys->tellDir = sys_tellDir;
    sys->seekDir = sys_seekDir;

    sys->format = sys_format;
    sys->mount = sys_mount;
    sys->unmount = sys_unmount;
    sys->remove = sys_remove;
    sys->rename = sys_rename;
    sys->disk_free = sys_free;
    sys->sleep = sys_sleep;
    sys->kill = sys_kill;
    sys->getpid = sys_getpid;
    sys->yield = sys_yield;
    sys->ready = sys_ready;
    //sys->create = 0;
    sys->reset = 0;
    sys->putc = sys_putc;
    sys->puts = sys_puts;
    sys->kbhit = 0;
    sys->readbyte = 0;
    sys->full_path = sys_full_path;
    sys->updatepath = sys_update_path;
    sys->malloc = sys_malloc;
    sys->free = sys_mfree;
    sys->self = sys_struct_task;
    sys->getpath = sys_get_path;
    sys->cd = sys_cd;
    sys->elf_execve=sys_elf_execve;
    sys->create = sys_create;
   // sys->js0n = sys_js0n;
    sys->freeHeap = sys_free_heap;
    exception_set_syscall_handler(do_syscall);
    return 0;
}

/*
char *loadConfig(char *path,int *size){
if(!disk.exist(path)){
    printf("error init shell\n");
    return NULL;
}
FILE *fs=disk.open(path,LFS_O_RDONLY);
int ssize = disk.size(fs);
char *jsonbuff=malloc(ssize+1);
disk.read(jsonbuff,ssize,fs);
disk.close(fs);
*size=ssize;
return jsonbuff;
}*/


struct irq_context *do_syscall(struct irq_context *ctx)
{
    uint32_t a0 = ctx->reg[REG_ARG0 + 0];
    uint32_t a1 = ctx->reg[REG_ARG0 + 1];
    uint32_t a2 = ctx->reg[REG_ARG0 + 2];
    uint32_t a3 = ctx->reg[REG_ARG0 + 3];
    uint32_t a4 = ctx->reg[REG_ARG0 + 4];
    uint32_t a5 = ctx->reg[REG_ARG0 + 5];
    uint32_t n  = ctx->reg[REG_ARG0 + 7];
    switch(n){
        case OS_FREE_HEAP:
           // ctx->reg[REG_RET]=heap_free();
            ctx->pc += 4;
        break;
        case OS_JSON:
            //ctx->reg[REG_RET]=js0n((char *)a0,a1,(char *)a2,a3,(size_t *)a4);
            //ctx->pc += 4;
        break;
        case OS_LOAD_ELF:
             //ctx->reg[REG_RET]=elf_execve((char *)a0,(exec_img *)a1);
             ctx->pc += 4;
        break;
        case OS_CD:
            {
             //cd((FILE *)a0);
             ctx->pc += 4;
            }
        break;
        case OS_SIZE:
             ///ctx->reg[REG_RET]=disk.size((FILE *)a0);
             ctx->pc += 4;
        break;
        case OS_GET_PATH:
            //ctx->reg[REG_RET]=full_path("");
            ctx->pc += 4;
        break;
        case OS_STRUCT_TASK:
            ctx->reg[REG_RET]=&proctab[a0];
            ctx->pc += 4;
        break;
        case OS_UPDATE_PATH:
            {
               // update_path();
                ctx->pc += 4;
            }
        break;
        case OS_GLOBAL_PATH:
            {
                //ctx->reg[REG_RET]=full_path((char *)a0);
                ctx->pc += 4;
            }
        break;

        case OS_EXIST:
             //ctx->reg[REG_RET]=disk.exist((char *)a0);
             ctx->pc += 4;
        break;
        case OS_YIELD:
             ctx->pc =(uint32)&resched;
        break;   
        case OS_SLEEP:
            //sleep(a0);
            ctx->pc += 4;
        break;
        case OS_FREE:
            //free((void *)a0);
            ctx->pc += 4;
        break;
        case OS_MALLOC:
            //ctx->reg[REG_RET] = malloc(a0);
            ctx->pc += 4;
        break;

        case OS_KILL:
            // kill(a0);
             ctx->pc += 4;
        break;
        case OS_NULLPROCESS:
            {
                /*int len;
                int size;
                char jsonp[100];
                char *jsonbuff=loadConfig("shell/shell.json",&size);
                char *val;

                memset(jsonp,0,100);
                val = js0n("loader",0,jsonbuff,size,&len);
                memcpy(jsonp,val,len);
                exec_img ximg;
                int (*p)(int,char **);
                int ret =elf_execve(jsonp,&ximg);
                if(ret == -1){
                    panic("error load\n");
                }
                p = (int *)ret;
                int child = create(p, 4096, 3, "shell", 0);

                task_t *prptr=& thrtab[child];
                prptr->elf = TRUE;
                prptr->img = (void *)ximg.start;
                ready(child);*/
            }
        case OS_PUTC:
            //printf("%c",a0);
            //sem_wait(&uart_tx);
            //UART=a0;
            //sem_signal(&uart_tx);
            //csr_put(a0);
            //ctx->pc += 4;
            //ctx->pc =(uint32)&start;
        break;
        break;
        case OS_PUTS:
            //sem_wait(&uart_tx);
            //print((char *)a0);
            //sem_signal(&uart_tx);
            //printf("%s", (char *)a0);
            //ctx->reg[REG_RET] = 0;
            //ctx->pc += 4;
        break;
        
        case OS_GETC:

        break;
        case OS_GETS:

        break;
        case OS_CLOSE:

        break;
        case OS_OPEN:

        break;
        case OS_READ:

        break;
        case OS_WRITE:

        break;
        case OS_CREATE:
             //ctx->reg[REG_RET]=create((void *)a0, a1, 3, (char *)a2, 0);
             ctx->pc += 4;
        break;
        case OS_READY:
            //ctx->reg[REG_RET]=ready(a0);
            ctx->pc += 4;
        break;
        case OS_SEMA_INIT:

        break;
        case OS_SEMA_SIGNAL:

        break;
        case OS_SEMA_WAIT:

        break;

        case OS_FOPEN:
            {
                //ctx->reg[REG_RET] = disk.open((char *)a0,a1);
                ctx->pc += 4;
            }
        break;
        case OS_FSEEK:
            {
                //ctx->reg[REG_RET] = disk.seek((FILE *)a0,a1,a2);
                ctx->pc += 4;
            }
        break;
        case OS_AVAILABLE:
            {
               // ctx->reg[REG_RET] = disk.available((FILE *)a0);
                ctx->pc += 4;
            }
        break;
        case OS_FREAD:
            {
                //ctx->reg[REG_RET] = disk.read((void *)a0,a1,(FILE *)a2);
                ctx->pc += 4;
            }
        break;
        case OS_FWRITE:
            {
                //ctx->reg[REG_RET] = disk.write((void *)a0,a1,(FILE *)a2);
                ctx->pc += 4;
            }
        break;
        case OS_FCLOSE:
            {
                //ctx->reg[REG_RET] = disk.close((FILE *)a0);
                ctx->pc += 4;
            }
        break;
        case OS_FTELL:
                {
                    //ctx->reg[REG_RET] = disk.tell((FILE *)a0);
                    ctx->pc += 4;
                }
        break;
        case OS_FEOF:

        break;
        case OS_REMOVE:
            {
                //ctx->reg[REG_RET] = disk.remove((char *)a0);
                ctx->pc += 4;
            }
        break;
        case OS_OPENDIR:
            {
                //ctx->reg[REG_RET] = disk.openDir((char *)a0);
                ctx->pc += 4;
            }
        break;
        case OS_READDIR:
            {
                //ctx->reg[REG_RET] = disk.readDir((DIR *)a0,(struct lfs_info *)a1);
                ctx->pc += 4;
            }
        break;
        case OS_CLOSEDIR:
            {
                //ctx->reg[REG_RET] = disk.closeDir((DIR *)a0);
                ctx->pc += 4;
            }
        break;
        case OS_MKDIR:
            {
                //ctx->reg[REG_RET] = disk.mkdir((char *)a0);
                ctx->pc += 4;
            }
        break;
        case OS_RENAME:
            {
                //ctx->reg[REG_RET] = disk.rename((char *)a0,(char *)a1);
                ctx->pc += 4;
            }
        break;
        case OS_FORMAT:
            {
                //ctx->reg[REG_RET] = disk.format((lfs_t *)a0,(struct lfs_config *)a1);
                ctx->pc += 4;
            }
        break;
        case OS_MOUNT:
            {
                //ctx->reg[REG_RET] = disk.mount((lfs_t *)a0,(struct lfs_config *)a1);
                ctx->pc += 4;
            }
        break;
        case OS_UNMOUNT:
            {
                //ctx->reg[REG_RET] = disk.unmount((lfs_t *)a0);
                ctx->pc += 4;
            }
        break;
        case OS_DISK_FREE:
            {
                //ctx->reg[REG_RET] = disk.free();
                ctx->pc += 4;
            }
        break;
        case OS_IS_DIR:

        break;
        case OS_FFLUSH:

        break;
        case OS_FGETC:

        break;
        case OS_FGETCS:

        break;
        case OS_FPUTC:

        break;
        case OS_FPUTCS:

        break;
        case OS_FGETPOS:

        break;
        case OS_NUM_TASK:

        break;
        default:
            kprintf("syscall no implement %x, %d\n",n,n);
            ctx->pc += 4;
        break;
    }
     
    return ctx;
}