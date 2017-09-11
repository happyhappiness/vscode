#include <sys/socket.h>
#include <sys/stat.h>

/* ---------------------------------- MASTER -------------------------------- */

void replicationFeedSlaves(list *slaves, int dictid, robj **argv, int argc) {
    listNode *ln;
    listIter li;
    int j;

    listRewind(slaves,&li);
    while((ln = listNext(&li))) {
        redisClient *slave = ln->value;
