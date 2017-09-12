    keyobj.type = REDIS_STRING;
    keyobj.ptr = ((char*)&keyname)+(sizeof(long)*2);

    decrRefCount(subst);

    /* printf("lookup '%s' => %p\n", keyname.buf,de); */
    return lookupKeyRead(db,&keyobj);
}
