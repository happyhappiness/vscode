                    bulklen < 0 || bulklen > 1024*1024*1024)
                {
                    c->argc--;
                    addReplyError(c,"invalid bulk write count");
                    resetClient(c);
                    return 1;
                }
