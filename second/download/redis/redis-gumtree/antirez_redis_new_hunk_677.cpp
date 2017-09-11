    return len;
}

/* Convert a long double into a string. If humanfriendly is non-zero
 * it does not use exponential format and trims trailing zeroes at the end,
 * however this results in loss of precision. Otherwise exp format is used
 * and the output of snprintf() is not modified.
 *
 * The function returns the length of the string or zero if there was not
 * enough buffer room to store it. */
int ld2string(char *buf, size_t len, long double value, int humanfriendly) {
    char buf[256];
    size_t l;

    if (isinf(value)) {
        /* Libc in odd systems (Hi Solaris!) will format infinite in a
         * different way, so better to handle it in an explicit way. */
        if (len < 5) return 0; /* No room. 5 is "-inf\0" */
        if (value > 0) {
            memcpy(buf,"inf",3);
            l = 3;
        } else {
            memcpy(buf,"-inf",4);
            l = 4;
        }
    } else if (humanfriendly) {
        /* We use 17 digits precision since with 128 bit floats that precision
         * after rounding is able to represent most small decimal numbers in a
         * way that is "non surprising" for the user (that is, most small
         * decimal numbers will be represented in a way that when converted
         * back into a string are exactly the same as what the user typed.) */
        l = snprintf(buf,len,"%.17Lf", value);
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
        if (l+1 > len) return 0; /* No room. */
    }
    buf[l] = '\0';
    return l;
}

/* Generate the Redis "Run ID", a SHA1-sized random number that identifies a
 * given execution of Redis, so that if you are talking with an instance
 * having run_id == A, and you reconnect and it has run_id == B, you can be
