
    /* convert val into string */
    char *buf;
    buf = zmalloc(sizeof(char) * 128);
    sprintf(buf, "%lld", val);
    return buf;
}
