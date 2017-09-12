addReplyErrorFormat(c,"Unrecognized REPLCONF option: %s",
                (char*)c->argv[j]->ptr);