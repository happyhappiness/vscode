char **make_exclude_list(char *fname,char **list1)
{
  char **list=list1;
  FILE *f = fopen(fname,"r");
  char line[MAXPATHLEN];
  if (!f) return list;

  while (fgets(line,MAXPATHLEN,f)) {
    int l = strlen(line);
    if (l && line[l-1] == '\n') l--;
    line[l] = 0;
    if (line[0]) add_exclude_list(line,&list);
  }
  fclose(f);
  return list;
}