        sentinelScriptJob *sj;

        if (WIFSIGNALED(statloc)) bysignal = WTERMSIG(statloc);
        sentinelEvent(REDIS_DEBUG,"-script-child",NULL,"%ld %d %d",
            (long)pid, exitcode, bysignal);

        ln = sentinelGetScriptListNodeByPid(pid);
        if (ln == NULL) {
            serverLog(REDIS_WARNING,"wait3() returned a pid (%ld) we can't find in our scripts execution queue!", (long)pid);
            continue;
        }
        sj = ln->value;
