static int tail_callback (void *data, char *buf, int buflen)
{
  cu_tail_match_t *obj = (cu_tail_match_t *) data;
  int i;

  for (i = 0; i < obj->matches_num; i++)
    match_apply (obj->matches[i].match, buf);

  return (0);
}