static void appendmem_to_linebuf(sed_eval_t *eval, const char* sz, int len)
{
    unsigned int reqsize = (eval->lspend - eval->linebuf) + len;
    if (eval->lsize < reqsize) {
        grow_line_buffer(eval, reqsize);
    }
    memcpy(eval->lspend, sz, len);
    eval->lspend += len;
}