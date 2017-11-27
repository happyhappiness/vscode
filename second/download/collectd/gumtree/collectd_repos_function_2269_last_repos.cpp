static int cu_tail_reopen(cu_tail_t *obj) {
  int seek_end = 0;
  FILE *fh;
  struct stat stat_buf = {0};
  int status;

  status = stat(obj->file, &stat_buf);
  if (status != 0) {
    char errbuf[1024];
    ERROR("utils_tail: stat (%s) failed: %s", obj->file,
          sstrerror(errno, errbuf, sizeof(errbuf)));
    return -1;
  }

  /* The file is already open.. */
  if ((obj->fh != NULL) && (stat_buf.st_ino == obj->stat.st_ino)) {
    /* Seek to the beginning if file was truncated */
    if (stat_buf.st_size < obj->stat.st_size) {
      INFO("utils_tail: File `%s' was truncated.", obj->file);
      status = fseek(obj->fh, 0, SEEK_SET);
      if (status != 0) {
        char errbuf[1024];
        ERROR("utils_tail: fseek (%s) failed: %s", obj->file,
              sstrerror(errno, errbuf, sizeof(errbuf)));
        fclose(obj->fh);
        obj->fh = NULL;
        return -1;
      }
    }
    memcpy(&obj->stat, &stat_buf, sizeof(struct stat));
    return 1;
  }

  /* Seek to the end if we re-open the same file again or the file opened
   * is the first at all or the first after an error */
  if ((obj->stat.st_ino == 0) || (obj->stat.st_ino == stat_buf.st_ino))
    seek_end = 1;

  fh = fopen(obj->file, "r");
  if (fh == NULL) {
    char errbuf[1024];
    ERROR("utils_tail: fopen (%s) failed: %s", obj->file,
          sstrerror(errno, errbuf, sizeof(errbuf)));
    return -1;
  }

  if (seek_end != 0) {
    status = fseek(fh, 0, SEEK_END);
    if (status != 0) {
      char errbuf[1024];
      ERROR("utils_tail: fseek (%s) failed: %s", obj->file,
            sstrerror(errno, errbuf, sizeof(errbuf)));
      fclose(fh);
      return -1;
    }
  }

  if (obj->fh != NULL)
    fclose(obj->fh);
  obj->fh = fh;
  memcpy(&obj->stat, &stat_buf, sizeof(struct stat));

  return 0;
}