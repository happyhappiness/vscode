static void sigchld_handler (int signal) /* {{{ */
{
  pid_t pid;
  int status;
  while ((pid = waitpid (-1, &status, WNOHANG)) > 0)
  {
    program_list_t *pl;
    for (pl = pl_head; pl != NULL; pl = pl->next)
      if (pl->pid == pid)
	break;
    if (pl != NULL)
      pl->status = status;
  } /* while (waitpid) */
}