#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <time.h>

void getFileStats(char* fileName, struct stat* s){

  char buffer[64];
  sprintf(buffer, "%ldB, %ldKB, %ldMB, %ldGB",s->st_size,s->st_size / 1024, s->st_size / 1046576, s->st_size / 1073741824);
  int temp = 0b100000000;

  printf("File stats for file [%s]:\n",fileName);
  printf("File size: %s\n",buffer);
  printf("File permissions: -");
  for(int x = 0; x < 9; x++){
    if((temp & s->st_mode) != 0){
      if((x % 3) == 0) printf("r");
      if((x % 3) == 1) printf("w");
      if((x % 3) == 2) printf("x");
    }else{
      printf("-");
    }

    temp >>= 1;
  }
  printf("\n");
  printf("User ID: %d | Group ID: %d\n",s->st_uid,s->st_gid);
  printf("Last time of access: %s",ctime(&(s->st_atime)));
  printf("Last time of modification: %s",ctime(&(s->st_mtime)));
  printf("Last time of status change: %s",ctime(&(s->st_ctime)));
}

int main(int argc, char* argv[]){
  struct stat* fileStats = malloc(sizeof(struct stat));

  if(stat(argv[1],fileStats) < 0){
    printf("Error getting stats on file\n");
    printf("%d: %s\n",errno, strerror(errno));
  }

  getFileStats(argv[1],fileStats);

  free(fileStats);

  return 0;
}
