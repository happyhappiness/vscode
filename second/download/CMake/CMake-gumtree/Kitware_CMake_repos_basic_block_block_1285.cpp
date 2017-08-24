(d = readdir(procdir); d; d = readdir(procdir)) {
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