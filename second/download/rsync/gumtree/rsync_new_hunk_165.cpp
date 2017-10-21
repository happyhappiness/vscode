  data_transfer=0;

  if (len > 0 && s->count>0) {
    build_hash_table(s);

    if (verbose > 2) 
      fprintf(FERROR,"built hash table\n");

    hash_search(f,s,buf,len);

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
    fprintf(FERROR, "false_alarms=%d tag_hits=%d matches=%d\n",
	    false_alarms, tag_hits, matches);

  total_tag_hits += tag_hits;
  total_false_alarms += false_alarms;
  total_matches += matches;
  total_data_transfer += data_transfer;
