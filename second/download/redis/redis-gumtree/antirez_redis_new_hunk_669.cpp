        if (l+1 > len) return 0; /* No room. */
        /* Now remove trailing zeroes after the '.' */
        if (strchr(buf,'.') != NULL) {
            char *p = buf+l-1;
            while(*p == '0') {
                p--;
                l--;
            }
            if (*p == '.') l--;
        }
    } else {
        l = snprintf(buf,len,"%.17Lg", value);
