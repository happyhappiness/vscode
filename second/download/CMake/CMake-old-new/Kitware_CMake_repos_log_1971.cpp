md5this = (unsigned char *) aprintf("%s:%s:%08x:%s:%s:%s",
                                        ha1,
                                        digest->nonce,
                                        digest->nc,
                                        digest->cnonce,
                                        digest->qop,
                                        ha2);