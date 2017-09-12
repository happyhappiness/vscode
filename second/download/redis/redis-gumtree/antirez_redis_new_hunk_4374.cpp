    keyname.buf[prefixlen+sublen+postfixlen] = '\0';
    keyname.len = prefixlen+sublen+postfixlen;

    initStaticStringObject(keyobj,((char*)&keyname)+(sizeof(long)*2))
    decrRefCount(subst);

    /* printf("lookup '%s' => %p\n", keyname.buf,de); */
