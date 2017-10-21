  int len=0;
  ioctl(fd,FIONREAD,&len);
  return(len);
}



/* this is taken from CVS */
int piped_child(char **command,int *f_in,int *f_out)
{
  int pid;
  int to_child_pipe[2];
