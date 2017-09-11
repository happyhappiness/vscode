            }
            if (j == ok_slaves[0] || errorcode != 0) {
                redisLog(REDIS_WARNING,
                "Closing slave %llu: child->slave RDB transfer failed: %s",
                    slave->id,
                    (errorcode == 0) ? "RDB transfer child aborted"
                                     : strerror(errorcode));
                freeClient(slave);
            } else {
                redisLog(REDIS_WARNING,
                "Slave %llu correctly received the streamed RDB file.",
                slave->id);
                /* Restore the socket as non-blocking. */
                anetNonBlock(NULL,slave->fd);
                anetSendTimeout(NULL,slave->fd,0);
