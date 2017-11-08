static void grow_gen_buffer(sed_eval_t *eval, int newsize,
                            char **gspend)
{
    if (gspend == NULL) {
        gspend = &eval->genbuf;
    }
    grow_buffer(eval->pool, &eval->genbuf, gspend,
                &eval->gsize, newsize);
    eval->lcomend = &eval->genbuf[71];
}