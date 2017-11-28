storeAppendPrintf(entry, "%s " SQUIDSTRINGPH "_%s %s %d " SQUIDSTRINGPH "\n",
                          name,
                          SQUIDSTRINGPRINT(cfg.key),
                          cfg.methodStr(), cfg.vectPointStr(), cfg.bypass,
                          SQUIDSTRINGPRINT(cfg.uri));