            listIter li;

            listRewind(server.slaves,&li);
            serverLog(LL_WARNING,"SYNC failed. BGSAVE failed");
            while((ln = listNext(&li))) {
                client *slave = ln->value;

                if (slave->replstate == SLAVE_STATE_WAIT_BGSAVE_START)
                    freeClient(slave);
            }
        }
