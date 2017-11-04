void add_exclude_list(char *pattern,char ***list)
{
  int len=0;
  if (list && *list)
    for (; (*list)[len]; len++) ;

  if (strcmp(pattern,"!") == 0) {
    if (verbose > 2)
      fprintf(stderr,"clearing exclude list\n");
    while ((len)--) 
      free((*list)[len]);
    free((*list));
    *list = NULL;
    return;
  }

  if (!*list) {
    *list = (char **)malloc(sizeof(char *)*2);
  } else {
    *list = (char **)realloc(*list,sizeof(char *)*(len+2));
  }

  if (!*list || !((*list)[len] = strdup(pattern)))
    out_of_memory("add_exclude");

  if (verbose > 2)
    fprintf(stderr,"add_exclude(%s)\n",pattern);
  
  (*list)[len+1] = NULL;
}