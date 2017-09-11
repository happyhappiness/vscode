
            /* Finally remove the selected key. */
            if (bestkey) {
                long long delta;

                robj *keyobj = createStringObject(bestkey,sdslen(bestkey));
                propagateExpire(db,keyobj);
                /* We compute the amount of memory freed by dbDelete() alone.
                 * It is possible that actually the memory needed to propagate
                 * the DEL in AOF and replication link is greater than the one
                 * we are freeing removing the key, but we can't account for
                 * that otherwise we would never exit the loop.
                 *
                 * AOF and Output buffer memory will be freed eventually so
                 * we only care about memory used by the key space. */
                delta = (long long) zmalloc_used_memory();
                dbDelete(db,keyobj);
                delta -= (long long) zmalloc_used_memory();
                // printf("%lld\n",delta);
                mem_freed += delta;
                server.stat_evictedkeys++;
                decrRefCount(keyobj);
                keys_freed++;

                /* When the memory to free starts to be big enough, we may
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
    }
    return REDIS_OK;
}

/* =================================== Main! ================================ */
