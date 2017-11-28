int
checkustr(RPC_UNICODE_STRING *string)
{

    if (string->pointer != 0) {
        uint32_t size,off,len;
        align(4);
        size = (uint32_t)((p[bpos]<<0) | (p[bpos+1]<<8) | (p[bpos+2]<<16) | (p[bpos+3]<<24));
        bpos = bpos+4;
        off = (uint32_t)((p[bpos]<<0) | (p[bpos+1]<<8) | (p[bpos+2]<<16) | (p[bpos+3]<<24));
        bpos = bpos+4;
        len = (uint32_t)((p[bpos]<<0) | (p[bpos+1]<<8) | (p[bpos+2]<<16) | (p[bpos+3]<<24));
        bpos = bpos+4;
        if (len > size || off != 0 ||
                string->length > string->maxlength || len != string->length/2) {
            debug((char *) "%s| %s: ERROR: RPC_UNICODE_STRING encoding error => size: %d len: %d/%d maxlength: %d offset: %d\n",
                  LogTime(), PROGRAM, size, len, string->length, string->maxlength, off);
            return -1;
        }
        /* UNICODE string */
        bpos = bpos+string->length;
    }
    return 0;
}