  int i, k;

  char buf[T_BLOCKSIZE];

  char *filename;

  char *pathname = 0;



#ifdef DEBUG

  printf("==> tar_extract_regfile(t=0x%lx, realname=\"%s\")\n", t,

