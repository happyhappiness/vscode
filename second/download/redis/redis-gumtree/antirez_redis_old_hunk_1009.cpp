            while((ln = listNext(&li))) {
                client *slave = listNodeValue(ln);
                char *state = NULL;
                char ip[REDIS_IP_STR_LEN];
                int port;
                long lag = 0;

                if (anetPeerToString(slave->fd,ip,sizeof(ip),&port) == -1) continue;
                switch(slave->replstate) {
                case REDIS_REPL_WAIT_BGSAVE_START:
                case REDIS_REPL_WAIT_BGSAVE_END:
                    state = "wait_bgsave";
                    break;
                case REDIS_REPL_SEND_BULK:
                    state = "send_bulk";
                    break;
                case REDIS_REPL_ONLINE:
                    state = "online";
                    break;
                }
                if (state == NULL) continue;
                if (slave->replstate == REDIS_REPL_ONLINE)
                    lag = time(NULL) - slave->repl_ack_time;

                info = sdscatprintf(info,
