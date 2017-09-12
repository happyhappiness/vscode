        return NULL;
    }

    prefixlen = p-spat;
    sublen = sdslen(ssub);
    postfixlen = sdslen(spat)-(prefixlen+1);
    memcpy(keyname.buf,spat,prefixlen);
    memcpy(keyname.buf+prefixlen,ssub,sublen);
    memcpy(keyname.buf+prefixlen+sublen,p+1,postfixlen);
    keyname.buf[prefixlen+sublen+postfixlen] = '\0';
    keyname.len = prefixlen+sublen+postfixlen;

    initStaticStringObject(keyobj,((char*)&keyname)+(sizeof(long)*2))
    decrRefCount(subst);

    /* printf("lookup '%s' => %p\n", keyname.buf,de); */
    return lookupKeyRead(db,&keyobj);
}

/* sortCompare() is used by qsort in sortCommand(). Given that qsort_r with
