    srand(seed);
    return rv;
}

static void putline(apr_file_t *f, const char *l)
{
    apr_file_puts(l, f);
}

/*
 * Make a password record from the given information.  A zero return
 * indicates success; failure means that the output buffer contains an
 * error message instead.
