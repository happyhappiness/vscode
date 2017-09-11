    errors.level = 0;

    /* Object types */
    sprintf(types[REDIS_STRING], "STRING");
    sprintf(types[REDIS_LIST], "LIST");
    sprintf(types[REDIS_SET], "SET");
    sprintf(types[REDIS_ZSET], "ZSET");
    sprintf(types[REDIS_HASH], "HASH");

    /* Object types only used for dumping to disk */
    sprintf(types[REDIS_EXPIRETIME], "EXPIRETIME");
    sprintf(types[REDIS_SELECTDB], "SELECTDB");
    sprintf(types[REDIS_EOF], "EOF");

    /* Double constants initialization */
    R_Zero = 0.0;
    R_PosInf = 1.0/R_Zero;
    R_NegInf = -1.0/R_Zero;
    R_Nan = R_Zero/R_Zero;

    process();

