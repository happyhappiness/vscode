    /* Currently we try to encode only strings */
    assert(o->type == REDIS_STRING);

    /* Check if it's possible to encode this value as a long. We are assuming
     * that sizeof(long) = sizeof(void) in all the supported archs. */
    value = strtol(s, &endptr, 10);
    if (endptr[0] != '\0') return REDIS_ERR;
    snprintf(buf,32,"%ld",value);

    /* If the number converted back into a string is not identical
     * then it's not possible to encode the string as integer */
    if (strlen(buf) != sdslen(s) || memcmp(buf,s,sdslen(s))) return REDIS_ERR;

    /* Ok, this object can be encoded */
    o->encoding = REDIS_ENCODING_INT;
