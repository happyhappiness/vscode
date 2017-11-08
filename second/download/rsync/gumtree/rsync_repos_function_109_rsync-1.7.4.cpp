void file_checksum(char *fname,char *sum,off_t size)
{
  off_t i;
  MDstruct MD;
  struct map_struct *buf;
  int fd;
  off_t len = size;
  char tmpchunk[CSUM_CHUNK];

  bzero(sum,csum_length);

  fd = open(fname,O_RDONLY);
  if (fd == -1) return;

  buf = map_file(fd,size);

  MDbegin(&MD);

  for(i = 0; i + CSUM_CHUNK <= len; i += CSUM_CHUNK) {
    bcopy(map_ptr(buf,i,CSUM_CHUNK),tmpchunk,CSUM_CHUNK);
    MDupdate(&MD, tmpchunk, CSUM_CHUNK*8);
  }

  if (len - i > 0) {
    bcopy(map_ptr(buf,i,len-i),tmpchunk,len-i);
    MDupdate(&MD, tmpchunk, (len-i)*8);
  }

  sum_put(&MD,sum);

  close(fd);
  unmap_file(buf);
}