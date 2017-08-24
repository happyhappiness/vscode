(fscanf(ps, KWSYSPE_PS_FORMAT, &pid, &ppid) == 2) {
        if (ppid == process_id) {
          /* Recursively kill this child and its children.  */
          kwsysProcessKill(pid);
        }
      }