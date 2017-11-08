static char *place(sed_eval_t *eval, char *asp, char *al1, char *al2)
{
    char *sp = asp;
    int n = al2 - al1;
    unsigned int reqsize = (sp - eval->genbuf) + n + 1;

    if (eval->gsize < reqsize) {
        grow_gen_buffer(eval, reqsize, &sp);
    }
    memcpy(sp, al1, n);
    return sp + n;
}