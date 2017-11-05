static void append_to_genbuf(sed_eval_t *eval, const char* sz, char **gspend)
{
    int len = strlen(sz);
    unsigned int reqsize = (*gspend - eval->genbuf) + len + 1;
    if (eval->gsize < reqsize) {
        grow_gen_buffer(eval, reqsize, gspend);
    }
    strcpy(*gspend, sz);
    /* *gspend will now point to NULL character */
    *gspend += len;
}