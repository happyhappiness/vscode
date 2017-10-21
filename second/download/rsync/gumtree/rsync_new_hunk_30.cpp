
void match_sums(int f,struct sum_struct *s,char *buf,off_t len)
{
  last_match = 0;
  false_alarms = 0;
  tag_hits = 0;
  matches=0;
  data_transfer=0;

  if (len > 0 && s->count>0) {
    build_hash_table(s);

    if (verbose > 2) 
      fprintf(stderr,"built hash table\n");
