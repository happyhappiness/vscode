    /* Currently we try to encode only strings */
    assert(o->type == REDIS_STRING);

    /* Check if we can represent this string as a long integer */
    if (isStringRepresentableAsLong(s,&value) == REDIS_ERR) return REDIS_ERR;

    /* Ok, this object can be encoded */
    o->encoding = REDIS_ENCODING_INT;
