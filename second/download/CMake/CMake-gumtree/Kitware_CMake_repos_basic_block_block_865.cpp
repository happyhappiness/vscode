{
  /* Check the specified path type.  */
  if (in_path[0] == '/') {
    /* Already a full path.  */
    strcpy(result, in_path);
  }
#if defined(_WIN32)
  else if (in_path[0] && in_path[1] == ':') {
    /* Already a full path.  */
    strcpy(result, in_path);
  }
#endif
  else {
    /* Relative to self path.  */
    char temp_path[KWSYS_SHARED_FORWARD_MAXPATH];
    strcpy(temp_path, self_path);
    strcat(temp_path, kwsys_shared_forward_path_slash);
    strcat(temp_path, in_path);
    if (!kwsys_shared_forward_realpath(temp_path, result)) {
      if (desc) {
        char msgbuf[KWSYS_SHARED_FORWARD_MAXPATH];
        kwsys_shared_forward_strerror(msgbuf);
        fprintf(stderr, "Error converting %s \"%s\" to real path: %s\n", desc,
                temp_path, msgbuf);
      }
      return 0;
    }
  }
  return 1;
}