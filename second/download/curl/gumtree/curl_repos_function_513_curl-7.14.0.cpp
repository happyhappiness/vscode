static void freedirs(struct FTP *ftp)
{
  int i;
  if(ftp->dirs) {
    for (i=0; i < ftp->dirdepth; i++){
      if(ftp->dirs[i]) {
        free(ftp->dirs[i]);
        ftp->dirs[i]=NULL;
      }
    }
    free(ftp->dirs);
    ftp->dirs = NULL;
  }
  if(ftp->file) {
    free(ftp->file);
    ftp->file = NULL;
  }
}