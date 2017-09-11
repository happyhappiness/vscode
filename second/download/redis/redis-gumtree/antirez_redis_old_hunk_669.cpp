        if (l+1 > len) return 0; /* No room. */
        /* Now remove trailing zeroes after the '.' */
        if (strchr(buf,'.') != NULL) {
            char *p = buf+len-1;
            while(*p == '0') {
                p--;
                len--;
            }
            if (*p == '.') len--;
        }
    } else {
        l = snprintf(buf,len,"%.17Lg", value);
