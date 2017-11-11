static void copy_to_linebuf(sed_eval_t *eval, const char* sz)
{
    eval->lspend = eval->linebuf;
    append_to_linebuf(eval, sz);
}