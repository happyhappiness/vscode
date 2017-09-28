                        obuf_pos = 0;
                    }
                }
                if (obuf_len == 0 && eof) break;
            }
        }
    }
    redisReaderFree(reader);
    printf("errors: %lld, replies: %lld\n", errors, replies);
    if (errors)
        exit(1);
    else
