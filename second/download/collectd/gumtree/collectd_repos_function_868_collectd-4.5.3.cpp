static int ctail_shutdown (void)
{
  int i;

  for (i = 0; i < tail_match_list_num; i++)
  {
    tail_match_destroy (tail_match_list[i]);
    tail_match_list[i] = NULL;
  }
  sfree (tail_match_list);
  tail_match_list_num = 0;

  return (0);
}