int is_vms_shell(void)
{
  char *shell;

  /* Have we checked the shell yet? */
  if(vms_shell >= 0)
    return vms_shell;

  shell = getenv("SHELL");

  /* No shell, means DCL */
  if(shell == NULL) {
    vms_shell = 1;
    return 1;
  }

  /* Have to make sure some one did not set shell to DCL */
  if(strcmp(shell, "DCL") == 0) {
    vms_shell = 1;
    return 1;
  }

  vms_shell = 0;
  return 0;
}