(!kwsys_shared_forward_realpath(temp_path, result)) {
      if (desc) {
        char msgbuf[KWSYS_SHARED_FORWARD_MAXPATH];
        kwsys_shared_forward_strerror(msgbuf);
        fprintf(stderr, "Error converting %s \"%s\" to real path: %s\n", desc,
                temp_path, msgbuf);
      }
      return 0;
    }