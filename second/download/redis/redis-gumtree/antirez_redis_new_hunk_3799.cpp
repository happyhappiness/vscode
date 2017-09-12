    } else if (c->multibulk) {
        if (c->bulklen == -1) {
            if (((char*)c->argv[0]->ptr)[0] != '$') {
                addReplyError(c,"multi bulk protocol error");
                resetClient(c);
                return 1;
            } else {
