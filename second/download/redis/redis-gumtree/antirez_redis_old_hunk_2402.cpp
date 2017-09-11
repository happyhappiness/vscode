                    &port,NULL) != REDIS_OK))
                return;
            c->slave_listening_port = port;
        } else {
            addReplyErrorFormat(c,"Unrecognized REPLCONF option: %s",
                (char*)c->argv[j]->ptr);
