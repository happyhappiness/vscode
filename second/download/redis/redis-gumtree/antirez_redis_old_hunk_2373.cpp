            int port;

            client = listNodeValue(ln);
            if (anetPeerToString(client->fd,ip,&port) == -1) continue;
            snprintf(addr,sizeof(addr),"%s:%d",ip,port);
            if (strcmp(addr,c->argv[2]->ptr) == 0) {
                addReply(c,shared.ok);
