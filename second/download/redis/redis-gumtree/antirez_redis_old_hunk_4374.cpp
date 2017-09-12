    keyname.buf[prefixlen+sublen+postfixlen] = '\0';
    keyname.len = prefixlen+sublen+postfixlen;

    keyobj.refcount = 1;
    keyobj.type = REDIS_STRING;
    keyobj.ptr = ((char*)&keyname)+(sizeof(long)*2);

    decrRefCount(subst);

    /* printf("lookup '%s' => %p\n", keyname.buf,de); */
