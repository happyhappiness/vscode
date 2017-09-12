    keyobj.type = REDIS_STRING;
    keyobj.ptr = ((char*)&keyname)+(sizeof(long)*2);

    de = dictFind(dict,&keyobj);
    /* printf("lookup '%s' => %p\n", keyname.buf,de); */
    if (!de) return NULL;
    return dictGetEntryVal(de);
}

/* sortCompare() is used by qsort in sortCommand(). Given that qsort_r with
