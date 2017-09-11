    vsnprintf(msg, sizeof(msg), fmt, ap);
    va_end(ap);

    printf("--- RDB ERROR DETECTED ---\n");
    printf("[offset %llu] %s\n",
        (unsigned long long) (rdbstate.rio ?
            rdbstate.rio->processed_bytes : 0), msg);
    printf("[additional info] While doing: %s\n",
        rdb_check_doing_string[rdbstate.doing]);
    if (rdbstate.key)
        printf("[additional info] Reading key '%s'\n",
            (char*)rdbstate.key->ptr);
    rdbShowGenericInfo();
}

/* Print informations during RDB checking. */
