static void grow_hold_buffer(sed_eval_t *eval, int newsize)
{
    grow_buffer(eval->pool, &eval->holdbuf, &eval->hspend,
                &eval->hsize, newsize);
}