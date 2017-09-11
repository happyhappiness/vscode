                    ssize_t nwritten = write(fd,obuf+obuf_pos,obuf_len);
                    
                    if (nwritten == -1) {
                        if (errno != EAGAIN && errno != EINTR) {
                            fprintf(stderr, "Error writing to the server: %s\n",
                                strerror(errno));
                            exit(1);
