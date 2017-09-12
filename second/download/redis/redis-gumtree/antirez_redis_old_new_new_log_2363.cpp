s = sdscatprintf(s,"... (%lu more bytes)",
                    (unsigned long)
                    sdslen(argv[j]->ptr) - SLOWLOG_ENTRY_MAX_STRING);