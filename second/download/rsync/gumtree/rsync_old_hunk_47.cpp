

static void build_hash_table(struct sum_struct *s)
{
  int i;

  targets = (struct target *)malloc(sizeof(targets[0])*s->count);
  if (!targets) out_of_memory("build_hash_table");

  for (i=0;i<s->count;i++) {
    targets[i].i = i;
    targets[i].t = gettag(s->sums[i].sum1);
  }

