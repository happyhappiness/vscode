static void freedirs(struct ftp_conn *ftpc)
{
  int i;
  if(ftpc->dirs) {
    for (i=0; i < ftpc->dirdepth; i++){
      if(ftpc->dirs[i]) {
        free(ftpc->dirs[i]);
        ftpc->dirs[i]=NULL;
      }
    }
    free(ftpc->dirs);
    ftpc->dirs = NULL;
  }
  if(ftpc->file) {
    free(ftpc->file);
    ftpc->file = NULL;
  }
}