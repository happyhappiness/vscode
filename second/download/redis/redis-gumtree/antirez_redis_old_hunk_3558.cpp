            appendServerSaveParams(seconds, changes);
        }
        sdsfreesplitres(v,vlen);
    } else {
        addReplyErrorFormat(c,"Unsupported CONFIG parameter: %s",
            (char*)c->argv[2]->ptr);
