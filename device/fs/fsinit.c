#include <os.h>
#include <littlefs.h>


status	fsinit(void){
kprintf("upload fs at (%08x)\n",(uint32)&fs);
upload_fs((uint32)&fs);
int ret;
int disk_free;
littlefs_init(&disk, &config, 500000);
#if 0
kprintf("startup_test: format    ");
ret = disk.format(disk.lfs, &config);
if(ret) 
{
    kprintf("[FAIL]\n");
    kprintf("Error Code: %d\n", ret);
    return ;
}
kprintf("[ OK ]\n");
#endif
kprintf("startup_test: mount     ");
ret = disk.mount(disk.lfs, &config);
if(ret) 
{
    kprintf("[FAIL]\n");
    kprintf("Error Code: %d\n", ret);
    return -1;
}

kprintf("[ OK ]\n");
disk_free = disk.free();
kprintf("startup_test: available size = %d Bytes\n", disk_free);

struct lfs_info info;

DIR *dir = disk.openDir("/");
if(dir==0){
    kprintf("not a directory ");
    return -1;
}
while (disk.readDir(dir, &info)> 0){
    if (strcmp(info.name, ".") && strcmp(info.name, "..") && strcmp(info.name, "//")){
        if(disk.exist(info.name)){
			if (info.type == LFS_TYPE_DIR){
               	kprintf(" /%s\n",info.name);
            }else{
                kprintf(" %s %d \n",info.name,info.size);
            }
        }
    }
}
disk.closeDir(dir);

return OK;
}