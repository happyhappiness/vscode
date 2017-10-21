
void add_exclude(char *pattern)
{
  add_exclude_list(pattern,&exclude_list);
}

char **make_exclude_list(char *fname,char **list1,int fatal)
{
  char **list=list1;
  FILE *f = fopen(fname,"r");
  char line[MAXPATHLEN];
  if (!f) {
    if (fatal) {
      fprintf(stderr,"%s : %s\n",fname,strerror(errno));
      exit(1);
    }
    return list;
  }

  while (fgets(line,MAXPATHLEN,f)) {
    int l = strlen(line);
    if (l && line[l-1] == '\n') l--;
    line[l] = 0;
    if (line[0]) add_exclude_list(line,&list);
