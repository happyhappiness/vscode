void
Ident::ReadReply(int fd, char *buf, size_t len, comm_err_t flag, int xerrno, void *data)
{
    IdentStateData *state = (IdentStateData *)data;
    char *ident = NULL;
    char *t = NULL;

    assert (buf == state->buf);

    if (flag != COMM_OK || len <= 0) {
        comm_close(fd);
        return;
    }

    /*
     * XXX This isn't really very tolerant. It should read until EOL
     * or EOF and then decode the answer... If the reply is fragmented
     * then this will fail
     */
    buf[len] = '\0';

    if ((t = strchr(buf, '\r')))
        *t = '\0';

    if ((t = strchr(buf, '\n')))
        *t = '\0';

    debugs(30, 5, "identReadReply: FD " << fd << ": Read '" << buf << "'");

    if (strstr(buf, "USERID")) {
        if ((ident = strrchr(buf, ':'))) {
            while (xisspace(*++ident));
            Ident::identCallback(state, ident);
        }
    }

    comm_close(fd);
}