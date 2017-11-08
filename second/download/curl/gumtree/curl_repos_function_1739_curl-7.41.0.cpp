static void freedirs(struct ftp_conn *ftpc)
{
  int i;
  if(ftpc->dirs) {
    for(i=0; i < ftpc->dirdepth; i++) {
      if(ftpc->dirs[i]) {
        free(ftpc->dirs[i]);
        ftpc->dirs[i]=NULL;
      }
    }
    free(ftpc->dirs);
    ftpc->dirs = NULL;
    ftpc->dirdepth = 0;
  }
  Curl_safefree(ftpc->file);

  /* no longer of any use */
  Curl_safefree(ftpc->newhost);
}