
        serverLog(LL_NOTICE,"Killing running AOF rewrite child: %ld",
            (long) server.aof_child_pid);
        if (kill(server.aof_child_pid,SIGUSR1) != -1) {
            while(wait3(&statloc,0,NULL) != server.aof_child_pid);
        }
        /* reset the buffer accumulating changes while the child saves */
        aofRewriteBufferReset();
        aofRemoveTempFile(server.aof_child_pid);
