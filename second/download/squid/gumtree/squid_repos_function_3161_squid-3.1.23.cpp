static void
gopherSendRequest(int fd, void *data)
{
    GopherStateData *gopherState = (GopherStateData *)data;
    char *buf = (char *)memAllocate(MEM_4K_BUF);

    if (gopherState->type_id == GOPHER_CSO) {
        const char *t = strchr(gopherState->request, '?');

        if (t != NULL)
            t++;		/* skip the ? */
        else
            t = "";

        snprintf(buf, 4096, "query %s\r\nquit\r\n", t);
    } else if (gopherState->type_id == GOPHER_INDEX) {
        char *t = strchr(gopherState->request, '?');

        if (t != NULL)
            *t = '\t';

        snprintf(buf, 4096, "%s\r\n", gopherState->request);
    } else {
        snprintf(buf, 4096, "%s\r\n", gopherState->request);
    }

    debugs(10, 5, "gopherSendRequest: FD " << fd);
    comm_write(fd, buf, strlen(buf), gopherSendComplete, gopherState, NULL);

    if (EBIT_TEST(gopherState->entry->flags, ENTRY_CACHABLE))
        gopherState->entry->setPublicKey();	/* Make it public */
}