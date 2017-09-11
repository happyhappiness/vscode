    errors.level = 0;

    /* Object types */
    sprintf(types[RDB_TYPE_STRING], "STRING");
    sprintf(types[RDB_TYPE_LIST], "LIST");
    sprintf(types[RDB_TYPE_SET], "SET");
    sprintf(types[RDB_TYPE_ZSET], "ZSET");
    sprintf(types[RDB_TYPE_HASH], "HASH");

    /* Object types only used for dumping to disk */
    sprintf(types[RDB_OPCODE_EXPIRETIME], "EXPIRETIME");
    sprintf(types[RDB_OPCODE_SELECTDB], "SELECTDB");
    sprintf(types[RDB_OPCODE_EOF], "EOF");

    process();

