            freeaddrinfo(bservinfo);
            if (!bound) {
                anetSetError(err, "bind: %s", strerror(errno));
                goto end;
            }
        }
        if (connect(s,p->ai_addr,p->ai_addrlen) == -1) {
