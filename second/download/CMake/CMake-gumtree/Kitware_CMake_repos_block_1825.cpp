{
    char msgbuf[KWSYS_SHARED_FORWARD_MAXPATH];
    kwsys_shared_forward_strerror(msgbuf);
    fprintf(stderr, "Error converting self path \"%s\" to real path: %s\n",
            self_path, msgbuf);
    return 0;
  }