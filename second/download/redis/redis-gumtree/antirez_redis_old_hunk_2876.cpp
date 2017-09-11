                 * start spending so much time here that is impossible to
                 * deliver data to the slaves fast enough, so we force the
                 * transmission here inside the loop. */
                if (slaves) {
                    listIter li;
                    listNode *ln;

                    listRewind(server.slaves,&li);
                    while((ln = listNext(&li))) {
                        redisClient *slave = listNodeValue(ln);
                        int events;

                        events = aeGetFileEvents(server.el,slave->fd);
                        printf("EVENTS: %d\n", events);
                        if (events & AE_WRITABLE &&
                            slave->replstate == REDIS_REPL_ONLINE &&
                            listLength(slave->reply))
                        {
                            printf("SLAVE %d -> %d\n",
                                slave->fd, (int) listLength(slave->reply));
                            sendReplyToClient(server.el,slave->fd,slave,0);
                        }
                    }
                }
            }
        }
        if (!keys_freed) return REDIS_ERR; /* nothing to free... */
