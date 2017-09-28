                        break;
                    }
                }
            }
            close(pipefds[0]);
            close(pipefds[1]);
        } else {
            server.stat_fork_time = ustime()-start;
            server.stat_fork_rate = (double) zmalloc_used_memory() * 1000000 / server.stat_fork_time / (1024*1024*1024); /* GB per second. */
            latencyAddSampleIfNeeded("fork",server.stat_fork_time/1000);

            serverLog(LL_NOTICE,"Background RDB transfer started by pid %d",
