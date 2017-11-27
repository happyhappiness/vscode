static int nfs_read(void) {
  FILE *fh;

  if ((fh = fopen("/proc/net/rpc/nfs", "r")) != NULL) {
    nfs_read_linux(fh, "client");
    fclose(fh);
  }

  if ((fh = fopen("/proc/net/rpc/nfsd", "r")) != NULL) {
    nfs_read_linux(fh, "server");
    fclose(fh);
  }

  return 0;
}