static int ipc_init (void) /* {{{ */
{
  pagesize_g = sysconf(_SC_PAGESIZE);
  return (0);
}