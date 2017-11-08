static apr_rmm_off_t find_block_of_size(apr_rmm_t *rmm, apr_size_t size)
{
    apr_rmm_off_t next = rmm->base->firstfree;
    apr_rmm_off_t best = 0;
    apr_rmm_off_t bestsize = 0;

    while (next) {
        struct rmm_block_t *blk = (rmm_block_t*)((char*)rmm->base + next);

        if (blk->size == size)
            return next;

        if (blk->size >= size) {
            /* XXX: sub optimal algorithm 
             * We need the most thorough best-fit logic, since we can
             * never grow our rmm, we are SOL when we hit the wall.
             */
            if (!bestsize || (blk->size < bestsize)) {
                bestsize = blk->size;
                best = next;
            }
        }

        next = blk->next;
    }

    if (bestsize > RMM_BLOCK_SIZE + size) {
        struct rmm_block_t *blk = (rmm_block_t*)((char*)rmm->base + best);
        struct rmm_block_t *new = (rmm_block_t*)((char*)rmm->base + best + size);

        new->size = blk->size - size;
        new->next = blk->next;
        new->prev = best;

        blk->size = size;
        blk->next = best + size;

        if (new->next) {
            blk = (rmm_block_t*)((char*)rmm->base + new->next);
            blk->prev = best + size;
        }
    }

    return best;
}