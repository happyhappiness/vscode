static int ctail_read (void)
{
  int success = 0;
  size_t i;

  for (i = 0; i < tail_match_list_num; i++)
  {
    int status;

    status = tail_match_read (tail_match_list[i]);
    if (status != 0)
    {
      ERROR ("tail plugin: tail_match_read[%zu] failed.", i);
    }
    else
    {
      success++;
    }
  }

  if (success == 0)
    return (-1);
  return (0);
}