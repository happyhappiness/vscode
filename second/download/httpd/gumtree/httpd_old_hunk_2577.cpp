                    node.ready = 0;
                }

                if (apr_table_get(hbt, "lastseen")) {
                    node.seen = atoi(apr_table_get(hbt, "lastseen"));
                } else {
                    node.seen = SEEN_TIMEOUT; 
                }
                seen = fage + node.seen;

                if (apr_table_get(hbt, "port")) {
                    node.port = atoi(apr_table_get(hbt, "port"));
                } else {
                    node.port = 80; 
                }
                apr_file_printf(fp, "%s &ready=%u&busy=%u&lastseen=%u&port=%u\n",
                                ip, node.ready, node.busy, (unsigned int) seen, node.port);
            } else {
                apr_time_t seen;
                seen = apr_time_sec(now - s->seen);
