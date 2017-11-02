void init_locks(void)
{
  gcry_control(GCRYCTL_SET_THREAD_CBS);
}