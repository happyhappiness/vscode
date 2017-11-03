static void build_hash_table(struct sum_struct *s)
{
  int i;

  if (!tag_table)
    tag_table = (tag *)malloc(sizeof(tag)*TABLESIZE);

  targets = (struct target *)malloc(sizeof(targets[0])*s->count);
  if (!tag_table || !targets) 
    out_of_memory("build_hash_table");

  for (i=0;i<s->count;i++) {
    targets[i].i = i;
    targets[i].t = gettag(s->sums[i].sum1);
  }

  qsort(targets,s->count,sizeof(targets[0]),(int (*)())compare_targets);

  for (i=0;i<TABLESIZE;i++)
    tag_table[i] = NULL_TAG;

  for (i=s->count-1;i>=0;i--) {    
    tag_table[targets[i].t] = i;
  }
}