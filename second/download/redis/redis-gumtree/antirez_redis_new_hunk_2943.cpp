        info = sdscatprintf(info,
            "connected_slaves:%d\r\n",
            listLength(server.slaves));
        if (listLength(server.slaves)) {
            int slaveid = 0;
            listNode *ln;
            listIter li;

            listRewind(server.slaves,&li);
            while((ln = listNext(&li))) {
                redisClient *slave = listNodeValue(ln);
                char *state = NULL;
                char ip[32];
                int port;

                if (anetPeerToString(slave->fd,ip,&port) == -1) continue;
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
                info = sdscatprintf(info,"slave%d:%s,%d,%s\r\n",
                    slaveid,ip,port,state);
                slaveid++;
            }
        }
    }

    /* CPU */
