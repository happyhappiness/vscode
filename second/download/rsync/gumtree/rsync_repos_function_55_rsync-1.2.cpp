void file_checksum(char *fname,char *sum,off_t size)
{
  char *buf;
  int fd;
  bzero(sum,SUM_LENGTH);

  fd = open(fname,O_RDONLY);
  if (fd == -1) return;

  buf = map_file(fd,size);
  if (!buf) {
    close(fd);
    return;
  }

  get_checksum2(buf,size,sum);
  close(fd);
  unmap_file(buf,size);
}