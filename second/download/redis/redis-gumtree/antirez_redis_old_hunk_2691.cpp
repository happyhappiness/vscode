                    ssize_t nwritten = write(fd,obuf+obuf_pos,obuf_len);
                    
                    if (nwritten == -1) {
                        fprintf(stderr, "Error writing to the server: %s\n",
                            strerror(errno));
                        exit(1);
                    }
                    obuf_len -= nwritten;
                    obuf_pos += nwritten;
