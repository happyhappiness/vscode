storeAppendPrintf(entry, "%s " SQUIDSTRINGPH " %s",
                              name, SQUIDSTRINGPRINT((*m)->name), ConfigParser::QuoteString((*v)->value));