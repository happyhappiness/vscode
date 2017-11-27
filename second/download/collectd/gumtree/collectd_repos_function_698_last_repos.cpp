static int mach_get_task_name(task_t t, int *pid, char *name,
                              size_t name_max_len) {
  int mib[4];

  struct kinfo_proc kp;
  size_t kp_size;

  mib[0] = CTL_KERN;
  mib[1] = KERN_PROC;
  mib[2] = KERN_PROC_PID;

  if (pid_for_task(t, pid) != KERN_SUCCESS)
    return -1;
  mib[3] = *pid;

  kp_size = sizeof(kp);
  if (sysctl(mib, 4, &kp, &kp_size, NULL, 0) != 0)
    return -1;

  if (name_max_len > (MAXCOMLEN + 1))
    name_max_len = MAXCOMLEN + 1;

  strncpy(name, kp.kp_proc.p_comm, name_max_len - 1);
  name[name_max_len - 1] = '\0';

  DEBUG("pid = %i; name = %s;", *pid, name);

  /* We don't do the special handling for `p_comm == "LaunchCFMApp"' as
   * `top' does it, because it is a lot of work and only used when
   * debugging. -octo */

  return 0;
}