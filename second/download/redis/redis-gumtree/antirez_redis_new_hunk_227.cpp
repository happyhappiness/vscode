            }
            close(pipefds[0]);
            close(pipefds[1]);
            closeChildInfoPipe();
        } else {
            serverLog(LL_NOTICE,"Background RDB transfer started by pid %d",
                childpid);
