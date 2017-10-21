  int len=0;
  if (list && *list)
    for (; (*list)[len]; len++) ;

  if (strcmp(pattern,"!") == 0) {
    if (verbose > 2)
      rprintf(FINFO,"clearing exclude list\n");
    while ((len)--) 
      free((*list)[len]);
    free((*list));
    *list = NULL;
    return;
  }
