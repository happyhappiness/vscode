void* runner(void* args)
{
  int cc;
  for (cc = 0; cc < 10; cc++) {
    printf("%p CC: %d\n", args, cc);
  }
  res++;
  return 0;
}