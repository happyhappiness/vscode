static apr_rmm_off_t find_block_by_offset(apr_rmm_t *rmm, apr_rmm_off_t next, 
                                          apr_rmm_off_t find, int includes)
{
    apr_rmm_off_t prev = 0;

    while (next) {
        struct rmm_block_t *blk = (rmm_block_t*)((char*)rmm->base + next);

        if (find == next)
            return next;

        /* Overshot? */
        if (find < next)
            return includes ? prev : 0;

        prev = next;
        next = blk->next;
    }
    return includes ? prev : 0;
}