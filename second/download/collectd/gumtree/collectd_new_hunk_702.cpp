  struct tm struct_tm;

  if (datadir != NULL) {
    size_t len = strlen(datadir) + 1;

    if (len >= ptr_size)
      return ENOBUFS;

    memcpy(ptr, datadir, len);
    ptr[len - 1] = '/';
    ptr_size -= len;
    ptr += len;
  }

  status = FORMAT_VL(ptr, ptr_size, vl);
  if (status != 0)
    return status;

  /* Skip all the time formatting stuff when printing to STDOUT or
   * STDERR. */
  if (use_stdio)
    return 0;

  ptr_size -= strlen(ptr);
  ptr += strlen(ptr);

  /* "-2013-07-12" => 11 bytes */
  if (ptr_size < 12) {
    ERROR("csv plugin: Buffer too small.");
    return ENOMEM;
  }

  /* TODO: Find a way to minimize the calls to `localtime_r',
   * since they are pretty expensive.. */
  now = time(NULL);
  if (localtime_r(&now, &struct_tm) == NULL) {
    ERROR("csv plugin: localtime_r failed");
    return -1;
  }

  status = strftime(ptr, ptr_size, "-%Y-%m-%d", &struct_tm);
  if (status == 0) /* yep, it returns zero on error. */
  {
    ERROR("csv plugin: strftime failed");
    return -1;
  }

  return 0;
} /* int value_list_to_filename */

static int csv_create_file(const char *filename, const data_set_t *ds) {
  FILE *csv;

  if (check_create_dir(filename))
    return -1;

  csv = fopen(filename, "w");
  if (csv == NULL) {
    char errbuf[1024];
    ERROR("csv plugin: fopen (%s) failed: %s", filename,
          sstrerror(errno, errbuf, sizeof(errbuf)));
    return -1;
  }

  fprintf(csv, "epoch");
  for (size_t i = 0; i < ds->ds_num; i++)
    fprintf(csv, ",%s", ds->ds[i].name);

