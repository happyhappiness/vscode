storeAppendPrintf(entry, "%s " SQUIDSTRINGPH " %s_%s %d " SQUIDSTRINGPH "%s\n",
                          name,
                          SQUIDSTRINGPRINT(cfg.key),
                          cfg.methodStr(), cfg.vectPointStr(), cfg.bypass,
                          SQUIDSTRINGPRINT(cfg.uri),

                          optConnectionEncryption);