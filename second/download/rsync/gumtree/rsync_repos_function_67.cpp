int main(int argc,char *argv[])
{
  char sum[SUM_LENGTH];
  int i,j;

  checksum_init();

  for (i=1;i<argc;i++) {
    struct stat st;
    if (stat(argv[i],&st) == 0) {
      file_checksum(argv[i],sum,st.st_size);
      for (j=0;j<SUM_LENGTH;j++)
	printf("%02X",(unsigned char)sum[j]);
      printf("  %s\n",argv[i]);
    }
  }
}