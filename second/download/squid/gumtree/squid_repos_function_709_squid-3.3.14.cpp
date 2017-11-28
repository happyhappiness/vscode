static int
free_symlists (void)
{
  symlist_chain *lists;

  lists = preloaded_symlists;
  while (lists)
    {
      symlist_chain *next = lists->next;
      FREE (lists);
      lists = next;
    }
  preloaded_symlists = 0;

  return 0;
}