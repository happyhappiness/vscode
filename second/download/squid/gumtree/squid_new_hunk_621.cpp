            if ( !iaddr.GetHostByName(hostname) ) {
                fprintf(stderr, "client: ERROR: Cannot resolve %s: Host unknown.\n", hostname);
                exit(1);
            }
        }

        iaddr.getAddrInfo(AI);
        if ((conn = socket(AI->ai_family, AI->ai_socktype, 0)) < 0) {
            perror("client: socket");
            Ip::Address::FreeAddrInfo(AI);
            exit(1);
        }
        Ip::Address::FreeAddrInfo(AI);

        if (localhost && client_comm_bind(conn, iaddr) < 0) {
            perror("client: bind");
            exit(1);
        }

        iaddr.setEmpty();
        if ( !iaddr.GetHostByName(hostname) ) {
            fprintf(stderr, "client: ERROR: Cannot resolve %s: Host unknown.\n", hostname);
            exit(1);
        }

        iaddr.port(port);

        if (opt_verbose) {
            char ipbuf[MAX_IPSTRLEN];
            fprintf(stderr, "Connecting... %s(%s)\n", hostname, iaddr.toStr(ipbuf, MAX_IPSTRLEN));
        }

        if (client_comm_connect(conn, iaddr, ping ? &tv1 : NULL) < 0) {
            char hostnameBuf[MAX_IPSTRLEN];
            iaddr.toUrl(hostnameBuf, MAX_IPSTRLEN);
            if (errno == 0) {
                fprintf(stderr, "client: ERROR: Cannot connect to %s: Host unknown.\n", hostnameBuf);
            } else {
                char tbuf[BUFSIZ];
                snprintf(tbuf, BUFSIZ, "client: ERROR: Cannot connect to %s", hostnameBuf);
                perror(tbuf);
            }
            exit(1);
        }
        if (opt_verbose) {
            char ipbuf[MAX_IPSTRLEN];
            fprintf(stderr, "Connected to: %s (%s)\n", hostname, iaddr.toStr(ipbuf, MAX_IPSTRLEN));
        }

        /* Send the HTTP request */
        fprintf(stderr, "Sending HTTP request ... ");
        bytesWritten = mywrite(conn, msg, strlen(msg));

        if (bytesWritten < 0) {
            perror("client: ERROR: write");
            exit(1);
        } else if ((unsigned) bytesWritten != strlen(msg)) {
            fprintf(stderr, "client: ERROR: Cannot send request?: %s\n", msg);
            exit(1);
        }
        fprintf(stderr, "done.\n");

        if (put_file) {
            fprintf(stderr, "Sending HTTP request payload ... ");
            int x;
            lseek(put_fd, 0, SEEK_SET);
            while ((x = read(put_fd, buf, sizeof(buf))) > 0) {

                x = mywrite(conn, buf, x);

