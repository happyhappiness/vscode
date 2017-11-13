fprintf(stderr, "crypt() failed: %s\n", 
                        apr_strerror(errno, errbuf, sizeof errbuf));