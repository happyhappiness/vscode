static FILE * vmsfopenread(const char *file, const char *mode) {
  struct_stat statbuf;
  int result;

  result = stat(file, &statbuf);

  switch (statbuf.st_fab_rfm) {
  case FAB$C_VAR:
  case FAB$C_VFC:
  case FAB$C_STMCR:
    return fopen(file, "r");
    break;
  default:
    return fopen(file, "r", "rfm=stmlf", "ctx=stm");
  }
}