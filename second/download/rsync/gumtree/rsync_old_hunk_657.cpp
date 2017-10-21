
static void build_hash_table(struct sum_struct *s)
{
  int i;

  if (!tag_table)
    tag_table = (int *)malloc(sizeof(tag_table[0])*TABLESIZE);

  targets = (struct target *)malloc(sizeof(targets[0])*s->count);
  if (!tag_table || !targets) 
    out_of_memory("build_hash_table");

  for (i=0;i<(int) s->count;i++) {
    targets[i].i = i;
    targets[i].t = gettag(s->sums[i].sum1);
