int do_cmd(char *cmd,char *machine,char *user,char *path,int *f_in,int *f_out)
{
  char *args[100];
  int i,argc=0;
  char *tok,*p;

  if (!cmd)
    cmd = getenv(RSYNC_RSH_ENV);
  if (!cmd)
    cmd = RSYNC_RSH;
  cmd = strdup(cmd);
  if (!cmd) 
    goto oom;

  for (tok=strtok(cmd," ");tok;tok=strtok(NULL," ")) {
    args[argc++] = tok;
  }

  if (user) {
    args[argc++] = "-l";
    args[argc++] = user;
  }
  args[argc++] = machine;

  args[argc++] = RSYNC_NAME;

  server_options(args,&argc);

  if (path && *path) {
    char *dir = strdup(path);
    p = strrchr(dir,'/');
    if (p) {
      *p = 0;
      args[argc++] = dir;
      p++;
    } else {
      args[argc++] = ".";
      p = dir;
    }
    if (p[0])
      args[argc++] = path;
  }

  args[argc] = NULL;

  if (verbose > 3) {
    fprintf(stderr,"cmd=");
    for (i=0;i<argc;i++)
      fprintf(stderr,"%s ",args[i]);
    fprintf(stderr,"\n");
  }

  return piped_child(args,f_in,f_out);

oom:
  out_of_memory("do_cmd");
  return 0; /* not reached */
}