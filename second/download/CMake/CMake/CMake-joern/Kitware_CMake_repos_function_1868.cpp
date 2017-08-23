static void kwsysProcessKill(pid_t process_id)
{
#if defined(__linux__) || defined(__CYGWIN__)
  DIR* procdir;
#endif

  /* Suspend the process to be sure it will not create more children.  */
  kill(process_id, SIGSTOP);

#if defined(__CYGWIN__)
  /* Some Cygwin versions seem to need help here.  Give up our time slice
     so that the child can process SIGSTOP before we send SIGKILL.  */
  usleep(1);
#endif

/* Kill all children if we can find them.  */
#if defined(__linux__) || defined(__CYGWIN__)
  /* First try using the /proc filesystem.  */
  if ((procdir = opendir("/proc")) != NULL) {
#if defined(MAXPATHLEN)
    char fname[MAXPATHLEN];
#elif defined(PATH_MAX)
    char fname[PATH_MAX];
#else
    char fname[4096];
#endif
    char buffer[KWSYSPE_PIPE_BUFFER_SIZE + 1];
    struct dirent* d;

    /* Each process has a directory in /proc whose name is the pid.
       Within this directory is a file called stat that has the
       following format:

         pid (command line) status ppid ...

       We want to get the ppid for all processes.  Those that have
       process_id as their parent should be recursively killed.  */
    for (d = readdir(procdir); d; d = readdir(procdir)) {
      int pid;
      if (sscanf(d->d_name, "%d", &pid) == 1 && pid != 0) {
        struct stat finfo;
        sprintf(fname, "/proc/%d/stat", pid);
        if (stat(fname, &finfo) == 0) {
          FILE* f = fopen(fname, "r");
          if (f) {
            size_t nread = fread(buffer, 1, KWSYSPE_PIPE_BUFFER_SIZE, f);
            fclose(f);
            buffer[nread] = '\0';
            if (nread > 0) {
              const char* rparen = strrchr(buffer, ')');
              int ppid;
              if (rparen && (sscanf(rparen + 1, "%*s %d", &ppid) == 1)) {
                if (ppid == process_id) {
                  /* Recursively kill this child and its children.  */
                  kwsysProcessKill(pid);
                }
              }
            }
          }
        }
      }
    }
    closedir(procdir);
  } else
#endif
  {
#if defined(KWSYSPE_PS_COMMAND)
    /* Try running "ps" to get the process information.  */
    FILE* ps = popen(KWSYSPE_PS_COMMAND, "r");

    /* Make sure the process started and provided a valid header.  */
    if (ps && fscanf(ps, "%*[^\n]\n") != EOF) {
      /* Look for processes whose parent is the process being killed.  */
      int pid, ppid;
      while (fscanf(ps, KWSYSPE_PS_FORMAT, &pid, &ppid) == 2) {
        if (ppid == process_id) {
          /* Recursively kill this child and its children.  */
          kwsysProcessKill(pid);
        }
      }
    }

    /* We are done with the ps process.  */
    if (ps) {
      pclose(ps);
    }
#endif
  }

  /* Kill the process.  */
  kill(process_id, SIGKILL);

#if defined(__APPLE__)
  /* On OS X 10.3 the above SIGSTOP occasionally prevents the SIGKILL
     from working.  Just in case, we resume the child and kill it
     again.  There is a small race condition in this obscure case.  If
     the child manages to fork again between these two signals, we
     will not catch its children.  */
  kill(process_id, SIGCONT);
  kill(process_id, SIGKILL);
#endif
}