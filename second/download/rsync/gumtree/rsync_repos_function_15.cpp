void add_cvs_excludes(void)
{
  char fname[MAXPATHLEN];
  char *p;
  int i;
  
  for (i=0; cvs_ignore_list[i]; i++)
    add_exclude(cvs_ignore_list[i]);

  if ((p=getenv("HOME"))) {
    sprintf(fname,"%s/.cvsignore",p);
    add_exclude_file(fname,0);
  }

  if ((p=getenv("CVSIGNORE"))) {
    char *tok;
    for (tok=strtok(p," "); tok; tok=strtok(NULL," "))
      add_exclude(tok);
  }
}