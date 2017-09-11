    return REDIS_ERR;
}

/* This is how rewriting of the append only file in background works:
 *
 * 1) The user calls BGREWRITEAOF
