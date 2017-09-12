        int len = sdslen(c->obuf) - c->written;
        int nwritten = write(c->fd, ptr, len);
        if (nwritten == -1) {
            if (errno != EPIPE)
                fprintf(stderr, "Writing to socket: %s\n", strerror(errno));
            freeClient(c);
            return;
        }
