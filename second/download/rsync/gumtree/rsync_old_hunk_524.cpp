	s1 += (buf[i]+CHAR_OFFSET); s2 += s1;
    }
    return (s1 & 0xffff) + (s2 << 16);
}


static void sum_put(MDstruct *md,char *sum)
{
  SIVAL(sum,0,md->buffer[0]);
  if (csum_length <= 4) return;
  SIVAL(sum,4,md->buffer[1]);
  if (csum_length <= 8) return;
  SIVAL(sum,8,md->buffer[2]);
  if (csum_length <= 12) return;
  SIVAL(sum,12,md->buffer[3]);
}


void get_checksum2(char *buf,int len,char *sum)
{
  int i;
  MDstruct MD;
  static char *buf1;
  static int len1;

  if (len > len1) {
    if (buf1) free(buf1);
    buf1 = (char *)malloc(len+4);
    len1 = len;
    if (!buf1) out_of_memory("get_checksum2");
  }

  MDbegin(&MD);

  memcpy(buf1,buf,len);
  if (checksum_seed) {
    SIVAL(buf1,len,checksum_seed);
    len += 4;
  }

  for(i = 0; i + CSUM_CHUNK <= len; i += CSUM_CHUNK) {
    MDupdate(&MD, buf1+i, CSUM_CHUNK*8);
  }
  if (len - i > 0)
    MDupdate(&MD, buf1+i, (len-i)*8);

  sum_put(&MD,sum);
}


void file_checksum(char *fname,char *sum,OFF_T size)
{
  OFF_T i;
  MDstruct MD;
  struct map_struct *buf;
  int fd;
  OFF_T len = size;
  char tmpchunk[CSUM_CHUNK];

  memset(sum,0,csum_length);

  fd = open(fname,O_RDONLY);
  if (fd == -1) return;

  buf = map_file(fd,size);

  MDbegin(&MD);

  for(i = 0; i + CSUM_CHUNK <= len; i += CSUM_CHUNK) {
    memcpy(tmpchunk, map_ptr(buf,i,CSUM_CHUNK), CSUM_CHUNK);
    MDupdate(&MD, tmpchunk, CSUM_CHUNK*8);
  }

  if (len - i > 0) {
    memcpy(tmpchunk, map_ptr(buf,i,len-i), len-i);
    MDupdate(&MD, tmpchunk, (len-i)*8);
  }

  sum_put(&MD,sum);

  close(fd);
  unmap_file(buf);
}


void checksum_init(void)
{
  if (remote_version >= 14)
