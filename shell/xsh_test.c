
#include <os.h>
#include <littlefs.h>
#include <aes.h>



char *read_file(const char *filename) {
    char *tmp=full_path(filename);
    if (tmp==NULL){
        update_path();
        return NULL;
    }
    if(!disk.exist(tmp)){
       printf("%s file not found!\n",tmp );
       update_path();
       return NULL;
    }

	FILE *fs=disk.open(tmp,LFS_O_RDWR);
    int size = disk.size(fs);
    printf("size file %d\n",size);

	char *input = (char *) malloc(size);
	disk.read(input,size,fs);
	input[size] = '\0';
    disk.close(fs);
	return input;
}
 
int run_script(const char *filename) {
	char *input = read_file(filename);
	
	free(input);
	return -1;
}


 

shellcmd xsh_test(int nargs, char *args[]){
  Byte block[16]={1, 2, 3, 4, 5, 6, 7, 8, 9, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16}; 
  Byte block2[16];
  memcpy(block2, block, 16);

  Byte key[32]={1, 2, 3, 4, 5, 6, 7, 8, 9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf, 0,
          0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x20,
          0x21, 0x22, 0x23, 0x24, 0x25, 0x26};  
  
 
  AES_setKey(key);


  AES256_encrypt(block);  
  for(int i=0;i<4;++i){
    printf(" %2x %2x %2x %2x\n", block[i+0], block[i+4], block[i+8], block[i+12]);
  }
  printf("\n");

  AES256_decrypt(block);  
  for(int i=0;i<16;++i){
    if(block[i]!=block2[i]){
      printf("ERROR.\n");
      return 1;
    }
  }
  printf("OK.\n");
  return 0;
  
    return run_script(args[1]);
}