                server.maxclients = bestlimit-CONFIG_MIN_RESERVED_FDS;
                if (server.maxclients < 1) {
                    serverLog(LL_WARNING,"Your current 'ulimit -n' "
                        "of %llu is not enough for Redis to start. "
                        "Please increase your open file limit to at least "
                        "%llu. Exiting.",
                        (unsigned long long) oldlimit,
