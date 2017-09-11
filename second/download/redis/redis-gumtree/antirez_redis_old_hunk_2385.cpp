                        strerror(errno));
                    exit(1);
                }
                if (nread > 0) redisReaderFeed(reader,ibuf,nread);
            } while(nread > 0);

            /* Consume replies. */
