                c->querybuf = sdsMakeRoomFor(c->querybuf,c->bulklen+2);
                pos = 0;
            } else {
#endif
                // printf("NOT HERE (arg %d) (pos %d)\n",c->argc, pos);
                c->argv[c->argc++] =
                    createStringObject(c->querybuf+pos,c->bulklen);
                pos += c->bulklen+2;
#ifdef REDIS_MBULK_BIG_ARG
            }
#endif
            c->bulklen = -1;
            c->multibulklen--;
        }
