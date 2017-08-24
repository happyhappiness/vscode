{
  struct {
    int pid;
    int thid[2];
    char accesspid;
    char accessthid;
    char asid[2];
    char loginname[8];
    char flag;
    char len;
  } Input_data;

  union {
    struct {
      char gthb[4];
      int pid;
      int thid[2];
      char accesspid;
      char accessthid[3];
      int lenused;
      int offsetProcess;
      int offsetConTTY;
      int offsetPath;
      int offsetCommand;
      int offsetFileData;
      int offsetThread;
    } Output_data;
    char buf[2048];
  } Output_buf;

  struct Output_path_type {
    char gthe[4];
    short int len;
    char path[1024];
  };

  int Input_length;
  int Output_length;
  void* Input_address;
  void* Output_address;
  struct Output_path_type* Output_path;
  int rv;
  int rc;
  int rsn;

  Input_length = PGTH_LEN;
  Output_length = sizeof(Output_buf);
  Output_address = &Output_buf;
  Input_address = &Input_data;
  memset(&Input_data, 0, sizeof Input_data);
  Input_data.flag |= PGTHAPATH;
  Input_data.pid = pid;
  Input_data.accesspid = PGTH_CURRENT;

#ifdef _LP64
  BPX4GTH(&Input_length,
          &Input_address,
          &Output_length,
          &Output_address,
          &rv,
          &rc,
          &rsn);
#else
  BPX1GTH(&Input_length,
          &Input_address,
          &Output_length,
          &Output_address,
          &rv,
          &rc,
          &rsn);
#endif

  if (rv == -1) {
    errno = rc;
    return -1;
  }

  /* Check highest byte to ensure data availability */
  assert(((Output_buf.Output_data.offsetPath >>24) & 0xFF) == 'A');

  /* Get the offset from the lowest 3 bytes */
  Output_path = (char*)(&Output_buf) +
                (Output_buf.Output_data.offsetPath & 0x00FFFFFF);

  if (Output_path->len >= len) {
    errno = ENOBUFS;
    return -1;
  }

  strncpy(buf, Output_path->path, len);

  return 0;
}