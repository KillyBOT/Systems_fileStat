#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <time.h>

void getFileStats(char* fileName, struct stat* s){
  printf("File stats for file [%s]:\n",fileName);
  printf("File size: %ld bytes\n",s->st_size);
  printf("File permissions: %o\n",s->st_mode);
  printf("User ID: %d | Group ID: %d\n",s->st_uid,s->st_gid);
  printf("Last time of access: %s",ctime(&(s->st_atime)));
  printf("Last time of modification: %s",ctime(&(s->st_mtime)));
  printf("Last time of status change: %s",ctime(&(s->st_ctime)));
}

int main(int argc, char* argv[]){
  int testFile = open("testFile", O_CREAT | O_RDWR | O_TRUNC, 0644);
  struct stat* fileStats = malloc(sizeof(struct stat));
  char* toWrite = "Hello there hehe";

  if(stat("testFile",fileStats) < 0){
    printf("Error getting stats on file\n");
    printf("%d: %s\n",errno, strerror(errno));
  }

  getFileStats("testFile",fileStats);

  write(testFile, toWrite, 17);

  free(fileStats);
  close(testFile);

  return 0;
}
