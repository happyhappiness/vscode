        unsigned char *zm = o->ptr;
        unsigned char *val;
        unsigned int vlen;
        robj *field;

        field = getDecodedObject(c->argv[2]);
        if (zipmapGet(zm,field->ptr,sdslen(field->ptr), &val,&vlen)) {
            addReplySds(c,sdscatprintf(sdsempty(),"$%u\r\n", vlen));
            addReplySds(c,sdsnewlen(val,vlen));
            addReply(c,shared.crlf);
            decrRefCount(field);
            return;
        } else {
            addReply(c,shared.nullbulk);
            decrRefCount(field);
            return;
        }
    } else {
