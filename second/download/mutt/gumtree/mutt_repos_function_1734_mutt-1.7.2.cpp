int mutt_wait_filter (pid_t pid)
{
  int rc;
  
  waitpid (pid, &rc, 0);
  mutt_unblock_signals_system (1);
  rc = WIFEXITED (rc) ? WEXITSTATUS (rc) : -1;
  
  return rc;
}