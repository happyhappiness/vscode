            adjustOpenFilesLimit();
            if (server.maxclients != ll) {
                addReplyErrorFormat(c,"The operating system is not able to handle the specified number of clients, try with %d", server.maxclients);
                server.maxclients = orig_value;
                return;
            }
            if ((unsigned int) aeGetSetSize(server.el) <
                server.maxclients + REDIS_EVENTLOOP_FDSET_INCR)
            {
                if (aeResizeSetSize(server.el,
                    server.maxclients + REDIS_EVENTLOOP_FDSET_INCR) == AE_ERR)
                {
                    addReplyError(c,"The event loop API used by Redis is not able to handle the specified number of clients");
