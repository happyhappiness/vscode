static void move_block(apr_rmm_t *rmm, apr_rmm_off_t this, int free)
{   
    struct rmm_block_t *blk = (rmm_block_t*)((char*)rmm->base + this);

    /* close the gap */
    if (blk->prev) {
        struct rmm_block_t *prev = (rmm_block_t*)((char*)rmm->base + blk->prev);
        prev->next = blk->next;
    }
    else {
        if (free) {
            rmm->base->firstused = blk->next;
        }
        else {
            rmm->base->firstfree = blk->next;
        }
    }
    if (blk->next) {
        struct rmm_block_t *next = (rmm_block_t*)((char*)rmm->base + blk->next);
        next->prev = blk->prev;
    }

    /* now find it in the other list, pushing it to the head if required */
    if (free) {
        blk->prev = find_block_by_offset(rmm, rmm->base->firstfree, this, 1);
        if (!blk->prev) {
            blk->next = rmm->base->firstfree;
            rmm->base->firstfree = this;
        }
    }
    else {
        blk->prev = find_block_by_offset(rmm, rmm->base->firstused, this, 1);
        if (!blk->prev) {
            blk->next = rmm->base->firstused;
            rmm->base->firstused = this;
        }
    }

    /* and open it up */
    if (blk->prev) {
        struct rmm_block_t *prev = (rmm_block_t*)((char*)rmm->base + blk->prev);
        if (free && (blk->prev + prev->size == this)) {
            /* Collapse us into our predecessor */
            prev->size += blk->size;
            this = blk->prev;
            blk = prev;
        }
        else {
            blk->next = prev->next;
            prev->next = this;
        }
    }

    if (blk->next) {
        struct rmm_block_t *next = (rmm_block_t*)((char*)rmm->base + blk->next);
        if (free && (this + blk->size == blk->next)) {
            /* Collapse us into our successor */
            blk->size += next->size;
            blk->next = next->next;
            if (blk->next) {
                next = (rmm_block_t*)((char*)rmm->base + blk->next);
                next->prev = this;
            }
        }
        else {
            next->prev = this;
        }
    }
}