    } else if (!strcasecmp(c->argv[1]->ptr,"kill") && c->argc == 3) {
        listRewind(server.clients,&li);
        while ((ln = listNext(&li)) != NULL) {
            char ip[REDIS_IP_STR_LEN], addr[REDIS_IP_STR_LEN+64];
            int port;

            client = listNodeValue(ln);
            if (anetPeerToString(client->fd,ip,sizeof(ip),&port) == -1) continue;
            /* IPV6: might want to wrap a v6 address in [] */
            snprintf(addr,sizeof(addr),"%s:%d",ip,port);
            if (strcmp(addr,c->argv[2]->ptr) == 0) {
                addReply(c,shared.ok);
                if (c == client) {
                    client->flags |= REDIS_CLOSE_AFTER_REPLY;
