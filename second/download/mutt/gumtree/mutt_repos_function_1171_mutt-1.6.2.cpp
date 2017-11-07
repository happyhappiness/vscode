static int is_descendant (THREAD *a, THREAD *b)
{
  while (a)
  {
    if (a == b)
      return (1);
    a = a->parent;
  }
  return (0);
}