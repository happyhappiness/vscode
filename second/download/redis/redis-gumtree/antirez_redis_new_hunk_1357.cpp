            memcpy(server.repl_master_runid, runid, offset-runid-1);
            server.repl_master_runid[REDIS_RUN_ID_SIZE] = '\0';
            server.repl_master_initial_offset = strtoll(offset,NULL,10);
            serverLog(REDIS_NOTICE,"Full resync from master: %s:%lld",
                server.repl_master_runid,
                server.repl_master_initial_offset);
        }
