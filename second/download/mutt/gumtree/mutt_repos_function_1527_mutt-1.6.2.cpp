static void disable_coredumps (void)
{
  struct rlimit rl = {0, 0};
  static short done = 0;

  if (!done)
  {
    setrlimit (RLIMIT_CORE, &rl);
    done = 1;
  }
}