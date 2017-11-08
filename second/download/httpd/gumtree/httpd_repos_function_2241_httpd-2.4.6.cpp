static void append_to_holdbuf(sed_eval_t *eval, const char* sz)
{
    int len = strlen(sz);
    unsigned int reqsize = (eval->hspend - eval->holdbuf) + len + 1;
    if (eval->hsize <= reqsize) {
        grow_hold_buffer(eval, reqsize);
    }
    strcpy(eval->hspend, sz);
    /* hspend will now point to NULL character */
    eval->hspend += len;
}