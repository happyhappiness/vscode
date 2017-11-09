curl_off_t VmsRealFileSize(const char *name,
                           const struct_stat *stat_buf)
{
  char buffer[8192];
  curl_off_t count;
  int ret_stat;
  FILE * file;

  file = fopen(name, FOPEN_READTEXT); /* VMS */
  if(file == NULL)
    return 0;

  count = 0;
  ret_stat = 1;
  while(ret_stat > 0) {
    ret_stat = fread(buffer, 1, sizeof(buffer), file);
    if(ret_stat != 0)
      count += ret_stat;
  }
  fclose(file);

  return count;
}