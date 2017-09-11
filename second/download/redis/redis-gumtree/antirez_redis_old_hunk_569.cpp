
            if (WIFSIGNALED(statloc)) bysignal = WTERMSIG(statloc);

            if (pid == server.rdb_child_pid) {
                backgroundSaveDoneHandler(exitcode,bysignal);
            } else if (pid == server.aof_child_pid) {
                backgroundRewriteDoneHandler(exitcode,bysignal);
