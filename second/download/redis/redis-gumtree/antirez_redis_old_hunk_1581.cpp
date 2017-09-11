
    /* convert val into string */
    char *buf;
    buf = malloc(sizeof(char) * 128);
    sprintf(buf, "%lld", val);
    return buf;
}
