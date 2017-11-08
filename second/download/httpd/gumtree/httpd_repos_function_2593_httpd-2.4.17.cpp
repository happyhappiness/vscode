static void append_to_linebuf(sed_eval_t *eval, const char* sz)
{
    int len = strlen(sz);
    /* Copy string including null character */
    appendmem_to_linebuf(eval, sz, len + 1);
    --eval->lspend; /* lspend will now point to NULL character */
}