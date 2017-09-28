                nread = read(fd,ibuf,sizeof(ibuf));
                if (nread == -1 && errno != EAGAIN && errno != EINTR) {
                    fprintf(stderr, "Error reading from the server: %s\n",
                        strerror(errno));
                    exit(1);
                }
                if (nread > 0) {
                    redisReaderFeed(reader,ibuf,nread);
                    last_read_time = time(NULL);
                }
            } while(nread > 0);

            /* Consume replies. */
            do {
                if (redisReaderGetReply(reader,(void**)&reply) == REDIS_ERR) {
                    fprintf(stderr, "Error reading replies from server\n");
