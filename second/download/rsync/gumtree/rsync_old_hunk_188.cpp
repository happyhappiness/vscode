    if (verbose > 2) 
      fprintf(FERROR,"done hash search\n");
  } else {
    matched(f,s,buf,len,len,-1);
  }

  if (targets) {
    free(targets);
    targets=NULL;
  }

  if (verbose > 2)
