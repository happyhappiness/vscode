
    hash_search(f,s,buf,len);

    if (verbose > 2) 
      fprintf(FERROR,"done hash search\n");
  } else {
    matched(f,s,buf,len,-1);
  }

  sum_end(file_sum);

  if (remote_version >= 14) {
    if (verbose > 2)
