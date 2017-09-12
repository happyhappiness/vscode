        unsigned char *zm = o->ptr;
        unsigned char *val;
        unsigned int vlen;

        if (zipmapGet(zm,c->argv[2]->ptr,sdslen(c->argv[2]->ptr), &val,&vlen)) {
            addReplySds(c,sdscatprintf(sdsempty(),"$%u\r\n", vlen));
            addReplySds(c,sdsnewlen(val,vlen));
            addReply(c,shared.crlf);
            return;
        } else {
            addReply(c,shared.nullbulk);
            return;
        }
    } else {
