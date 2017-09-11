    vsnprintf(msg, sizeof(msg), fmt, ap);
    va_end(ap);

    printf("*** RDB CHECK FAILED: %s ***\n", msg);
    printf("AT RDB OFFSET: %llu\n",
        (unsigned long long) (rdbstate.rio ?
            rdbstate.rio->processed_bytes : 0));
    if (rdbstate.key)
        printf("READING KEY: %s\n", (char*)rdbstate.key->ptr);
}

/* Print informations during RDB checking. */
