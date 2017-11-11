static void copy_to_genbuf(sed_eval_t *eval, const char* sz)
{
    int len = strlen(sz);
    unsigned int reqsize = len + 1;
    if (eval->gsize < reqsize) {
        grow_gen_buffer(eval, reqsize, NULL);
    }
}