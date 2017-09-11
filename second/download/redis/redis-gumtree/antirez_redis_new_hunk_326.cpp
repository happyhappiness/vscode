    if (rdbstate.key)
        printf("[additional info] Reading key '%s'\n",
            (char*)rdbstate.key->ptr);
    if (rdbstate.key_type != -1)
        printf("[additional info] Reading type %d (%s)\n",
            rdbstate.key_type,
            ((unsigned)rdbstate.key_type <
             sizeof(rdb_type_string)/sizeof(char*)) ?
                rdb_type_string[rdbstate.key_type] : "unknown");
    rdbShowGenericInfo();
}

