int fileExists(char* filename)
{
#ifndef R_OK
#define R_OK 04
#endif
  if (access(filename, R_OK) != 0) {
    printf("Cannot find file: %s\n", filename);
    return 0;
  }
  return 1;
}