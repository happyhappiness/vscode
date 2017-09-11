                c->repl_ack_off = offset;
            c->repl_ack_time = server.unixtime;
            /* Note: this command does not reply anything! */
            return;
        } else {
            addReplyErrorFormat(c,"Unrecognized REPLCONF option: %s",
                (char*)c->argv[j]->ptr);
