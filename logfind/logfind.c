#include "dbg.h"
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

char * getHomeDir()
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

char ** getLogFiles(const char * myHome)
{
  const char* logfind_name = "/.logfind";
  char* logfind_fullpath = malloc(strlen(myHome) + strlen(logfind_name));
  strncpy(logfind_fullpath, myHome, strlen(myHome));
  strncat(logfind_fullpath, logfind_name, strlen(logfind_name));
  printf("logfind_fullpath: %c", *logfind_fullpath);
  check(access(myHome, F_OK ) != -1, "Coulnd't find .logfind file %c", *logfind_fullpath);

  error:
    if(logfind_fullpath) {
      free(logfind_fullpath);
    }
    return NULL;
}

int main(int argc, char *argv[])
{

  FILE *file;
  char * myHome = getHomeDir();
  char ** myLogfiles = getLogFiles(myHome);

  free(myHome);
  return 0;
error:
  if (myHome) {
    free(myHome);
  }
  return -1;
}
