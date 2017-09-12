        return NULL;
    }

    /* Find out if we're dealing with a hash dereference. */
    if ((f = strstr(p+1, "->")) != NULL) {
        fieldlen = sdslen(spat)-(f-spat);
        /* this also copies \0 character */
        memcpy(fieldname.buf,f+2,fieldlen-1);
        fieldname.len = fieldlen-2;
    } else {
        fieldlen = 0;
    }

    prefixlen = p-spat;
    sublen = sdslen(ssub);
    postfixlen = sdslen(spat)-(prefixlen+1)-fieldlen;
    memcpy(keyname.buf,spat,prefixlen);
    memcpy(keyname.buf+prefixlen,ssub,sublen);
    memcpy(keyname.buf+prefixlen+sublen,p+1,postfixlen);
    keyname.buf[prefixlen+sublen+postfixlen] = '\0';
    keyname.len = prefixlen+sublen+postfixlen;
    decrRefCount(subst);

    /* Lookup substituted key */
    initStaticStringObject(keyobj,((char*)&keyname)+(sizeof(long)*2));
    o = lookupKeyRead(db,&keyobj);

    if (o != NULL && fieldlen > 0) {
        /* Retrieve value from hash by the field name. This operation
         * already increases the refcount of the returned object. */
        if (o->type != REDIS_HASH || fieldname.len < 1) {
            return NULL;
        }
        initStaticStringObject(fieldobj,((char*)&fieldname)+(sizeof(long)*2));
        o = hashGet(o, &fieldobj);
    } else {
        if (o->type != REDIS_STRING) {
            return NULL;
        }

        /* Every object that this function returns needs to have its refcount
         * increased. sortCommand decreases it again. */
        incrRefCount(o);
    }

    return o;
}

/* sortCompare() is used by qsort in sortCommand(). Given that qsort_r with
