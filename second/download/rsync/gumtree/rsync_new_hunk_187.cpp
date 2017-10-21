      --k;
    }

  } while (++offset < end);

  matched(f,s,buf,len,len,-1);
  window_ptr(buf,len-1,1);
}


void match_sums(int f,struct sum_struct *s,struct map_struct *buf,off_t len)
{
  char file_sum[SUM_LENGTH];

  last_match = 0;
  false_alarms = 0;
  tag_hits = 0;
  matches=0;
  data_transfer=0;

  sum_init();

  if (len > 0 && s->count>0) {
    build_hash_table(s);

    if (verbose > 2) 
      fprintf(FERROR,"built hash table\n");

