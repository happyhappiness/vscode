            if (server.logfile) {
                /* Test if we are able to open the file. The server will not
                 * be able to abort just for this problem later... */
                fp = fopen(server.logfile,"a");
                if (fp == NULL) {
                    err = sdscatprintf(sdsempty(),
                        "Can't open the log file: %s", strerror(errno));
                    goto loaderr;
                }
                fclose(fp);
            }
        } else if (!strcasecmp(argv[0],"databases") && argc == 2) {
            server.dbnum = atoi(argv[1]);
