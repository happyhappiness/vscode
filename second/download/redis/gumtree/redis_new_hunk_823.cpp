    } else {
        if ((val = sdsnewlen(NULL,len)) == NULL) goto err;
    }

    /* Load the compressed representation and uncompress it to target. */
    if (rioRead(rdb,c,clen) == 0) goto err;
    if (lzf_decompress(c,clen,val,len) == 0) {
        if (rdbCheckMode) rdbCheckSetError("Invalid LZF compressed string");
        goto err;
    }
    zfree(c);

    if (plain)
        return val;
    else
        return createObject(OBJ_STRING,val);
