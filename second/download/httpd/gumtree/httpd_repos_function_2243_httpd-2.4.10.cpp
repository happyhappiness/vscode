static void grow_line_buffer(sed_eval_t *eval, int newsize)
{
    grow_buffer(eval->pool, &eval->linebuf, &eval->lspend,
                &eval->lsize, newsize);
}