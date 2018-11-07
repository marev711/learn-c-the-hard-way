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
  home_dir = malloc(strlen(pw->pw_dir) * sizeof(char*));
  home_dir = strdup(pw->pw_dir);
  return home_dir;
error:
  if (home_dir != NULL) {
    free(home_dir);
  }
  return -1;
}


int main(int argc, char *argv[])
{

  FILE *file;
  char * myHome = getHomeDir();
  printf("My home dir is: %s\n", myHome);
  free(myHome);
  //if access("

  return 0;
error:
  return -1;
}
