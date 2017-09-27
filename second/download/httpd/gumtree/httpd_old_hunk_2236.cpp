    while (--n >= 0) {
        *s++ = itoa64[v&0x3f];
        v >>= 6;
    }
}

static void putline(apr_file_t *f, const char *l)
{
    apr_file_puts(l, f);
}

/*
