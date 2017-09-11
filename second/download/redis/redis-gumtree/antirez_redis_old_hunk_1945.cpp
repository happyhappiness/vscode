    size_t buflen = 16;

    while(1) {
        buf = zmalloc(buflen);
        if (buf == NULL) return NULL;
        buf[buflen-2] = '\0';
        va_copy(cpy,ap);
        vsnprintf(buf, buflen, fmt, cpy);
        if (buf[buflen-2] != '\0') {
            zfree(buf);
            buflen *= 2;
            continue;
        }
        break;
    }
    t = sdscat(s, buf);
    zfree(buf);
    return t;
}

