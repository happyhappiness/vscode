    *biggest_input_buffer = bib;
}

void clientCommand(redisClient *c) {
    listNode *ln;
    listIter li;
    redisClient *client;

    if (!strcasecmp(c->argv[1]->ptr,"list") && c->argc == 2) {
        sds o = sdsempty();
        time_t now = time(NULL);

        listRewind(server.clients,&li);
        while ((ln = listNext(&li)) != NULL) {
            char ip[32], flags[16], *p;
            int port;

            client = listNodeValue(ln);
            if (anetPeerToString(client->fd,ip,&port) == -1) continue;
            p = flags;
            if (client->flags & REDIS_SLAVE) {
                if (client->flags & REDIS_MONITOR)
                    *p++ = 'O';
                else
                    *p++ = 'S';
            }
            if (client->flags & REDIS_MASTER) *p++ = 'M';
            if (p == flags) *p++ = 'N';
            if (client->flags & REDIS_MULTI) *p++ = 'x';
            if (client->flags & REDIS_BLOCKED) *p++ = 'b';
            if (client->flags & REDIS_IO_WAIT) *p++ = 'i';
            if (client->flags & REDIS_DIRTY_CAS) *p++ = 'd';
            if (client->flags & REDIS_CLOSE_AFTER_REPLY) *p++ = 'c';
            if (client->flags & REDIS_UNBLOCKED) *p++ = 'u';
            *p++ = '\0';
            o = sdscatprintf(o,
                "addr=%s:%d fd=%d idle=%ld flags=%s db=%d sub=%d psub=%d\n",
                ip,port,client->fd,
                (long)(now - client->lastinteraction),
                flags,
                client->db->id,
                (int) dictSize(client->pubsub_channels),
                (int) listLength(client->pubsub_patterns));
        }
        addReplyBulkCBuffer(c,o,sdslen(o));
        sdsfree(o);
    } else if (!strcasecmp(c->argv[1]->ptr,"kill") && c->argc == 3) {
        listRewind(server.clients,&li);
        while ((ln = listNext(&li)) != NULL) {
            char ip[32], addr[64];
            int port;

            client = listNodeValue(ln);
            if (anetPeerToString(client->fd,ip,&port) == -1) continue;
            snprintf(addr,sizeof(addr),"%s:%d",ip,port);
            if (strcmp(addr,c->argv[2]->ptr) == 0) {
                addReply(c,shared.ok);
                if (c == client) {
                    client->flags |= REDIS_CLOSE_AFTER_REPLY;
                } else {
                    freeClient(client);
                }
                return;
            }
        }
        addReplyError(c,"No such client");
    } else {
        addReplyError(c, "Syntax error, try CLIENT (LIST | KILL ip:port)");
    }
}
