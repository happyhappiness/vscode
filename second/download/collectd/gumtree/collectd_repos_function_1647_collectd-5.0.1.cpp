static int ctail_init (void)
{
  if (tail_match_list_num == 0)
  {
    WARNING ("tail plugin: File list is empty. Returning an error.");
    return (-1);
  }

  return (0);
}