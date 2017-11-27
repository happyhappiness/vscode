static int ipc_read (void) /* {{{ */
{
  int x = 0;
  x |= ipc_read_shm();
  x |= ipc_read_sem();
  x |= ipc_read_msg();

  return (x);
}