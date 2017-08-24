(ppid == process_id) {
          /* Recursively kill this child and its children.  */
          kwsysProcessKill(pid);
        }