static int notify_upstart(void) {
  char const *upstart_job = getenv("UPSTART_JOB");

  if (upstart_job == NULL)
    return 0;

  if (strcmp(upstart_job, "collectd") != 0) {
    WARNING("Environment specifies unexpected UPSTART_JOB=\"%s\", expected "
            "\"collectd\". Ignoring the variable.",
            upstart_job);
    return 0;
  }

  NOTICE("Upstart detected, stopping now to signal readyness.");
  raise(SIGSTOP);
  unsetenv("UPSTART_JOB");

  return 1;
}