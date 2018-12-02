#include "dbg.h"
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_NO_OF_LOGFILES 100

char* getHomeDir()
{
  char * home_dir = NULL;
  // Get HOME dir for current user
  uid_t uid = getuid();
  struct passwd *pw = getpwuid(uid);

  check(pw != NULL, "Failed to retrieve HOME for uid=%u", uid)
  home_dir = strdup(pw->pw_dir);
  return home_dir;
error:
  if (home_dir != NULL) {
    free(home_dir);
  }
  return NULL;
}

void deallocate_logfiles(char** logfiles)
{
  for (int i=0; i<MAX_NO_OF_LOGFILES; i++){
    if (logfiles[i]){
      free(logfiles[i]);
    }
  }
  if (logfiles){
    free(logfiles);
  }
}

char** getLogFiles(const char* myHome)
{
  const char* logfind_name = "/.logfind\0";
  char* logfind_fullpath = malloc(strlen(myHome) + strlen(logfind_name) + 1);
  logfind_fullpath[0] = '\0';
  strncpy(logfind_fullpath, myHome, strlen(myHome) + 1);
  strncat(logfind_fullpath, logfind_name, strlen(logfind_name));
  printf("logfind_fullpath: %s", logfind_fullpath);
  check(access(logfind_fullpath, F_OK ) != -1, "Coulnd't find the .logfind file %c", *logfind_fullpath);

  // Set up logfile pointer to pointer
  char** logfiles = malloc(MAX_NO_OF_LOGFILES * sizeof(char*));
  for (int i=0; i<MAX_NO_OF_LOGFILES; i++){
    logfiles[i] = NULL;
  }

  //deallocate_logfiles(logfiles);
  return logfiles;
  error:
    if(logfind_fullpath) {
      free(logfind_fullpath);
    }
    deallocate_logfiles(logfiles);
    return NULL;
}

int main(int argc, char *argv[])
{

  FILE *file;
  char * myHome = getHomeDir();
  char ** myLogfiles = getLogFiles(myHome);

  deallocate_logfiles(myLogfiles);
  free(myHome);
  return 0;
error:
if (myHome) {
  free(myHome);
}
if (myLogfiles) {
  deallocate_logfiles(myLogfiles);
}
  return -1;
}
