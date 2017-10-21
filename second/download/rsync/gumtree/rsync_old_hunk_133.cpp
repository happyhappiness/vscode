  unmap_file(buf,size);
}


void checksum_init(void)
{
  tmpchunk = (char *)malloc(CSUM_CHUNK);
  if (!tmpchunk) out_of_memory("checksum_init");
}


#ifdef CHECKSUM_MAIN
 int main(int argc,char *argv[])
{
