    }
}

/* This function is used in order to proxy what we receive from our master
 * to our sub-slaves. */
#include <ctype.h>
void replicationFeedSlavesFromMasterStream(list *slaves, char *buf, size_t buflen) {
    listNode *ln;
    listIter li;

    {
        printf("%zu:",buflen);
        for (size_t j = 0; j < buflen; j++) {
            printf("%c", isprint(buf[j]) ? buf[j] : '.');
        }
        printf("\n");
    }

    if (server.repl_backlog) feedReplicationBacklog(buf,buflen);
    listRewind(slaves,&li);
    while((ln = listNext(&li))) {
        client *slave = ln->value;

        /* Don't feed slaves that are still waiting for BGSAVE to start */
        if (slave->replstate == SLAVE_STATE_WAIT_BGSAVE_START) continue;
        addReplyString(slave,buf,buflen);
    }
}

void replicationFeedMonitors(client *c, list *monitors, int dictid, robj **argv, int argc) {
    listNode *ln;
    listIter li;
