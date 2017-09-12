    keyobj.type = REDIS_STRING;
    keyobj.ptr = ((char*)&keyname)+(sizeof(long)*2);

    /* printf("lookup '%s' => %p\n", keyname.buf,de); */
    return lookupKeyRead(db,&keyobj);
}

/* sortCompare() is used by qsort in sortCommand(). Given that qsort_r with
