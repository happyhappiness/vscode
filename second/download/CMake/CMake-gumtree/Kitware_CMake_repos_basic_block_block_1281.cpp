(rparen && (sscanf(rparen + 1, "%*s %d", &ppid) == 1)) {
                if (ppid == process_id) {
                  /* Recursively kill this child and its children.  */
                  kwsysProcessKill(pid);
                }
              }