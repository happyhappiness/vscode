{
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
  }