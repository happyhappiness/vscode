static int psprintf_flush(apr_vformatter_buff_t *vbuff)
{
    struct psprintf_data *ps = (struct psprintf_data *)vbuff;
    apr_memnode_t *node, *active;
    apr_size_t cur_len, size;
    char *strp;
    apr_pool_t *pool;
    apr_size_t free_index;

    pool = ps->pool;
    active = ps->node;
    strp = ps->vbuff.curpos;
    cur_len = strp - active->first_avail;
    size = cur_len << 1;

    /* Make sure that we don't try to use a block that has less
     * than APR_PSPRINTF_MIN_STRINGSIZE bytes left in it.  This
     * also catches the case where size == 0, which would result
     * in reusing a block that can't even hold the NUL byte.
     */
    if (size < APR_PSPRINTF_MIN_STRINGSIZE)
        size = APR_PSPRINTF_MIN_STRINGSIZE;

    node = active->next;
    if (!ps->got_a_new_node && size <= node_free_space(node)) {

        list_remove(node);
        list_insert(node, active);

        node->free_index = 0;

        pool->active = node;

        free_index = (APR_ALIGN(active->endp - active->first_avail + 1,
                                BOUNDARY_SIZE) - BOUNDARY_SIZE) >> BOUNDARY_INDEX;

        active->free_index = (APR_UINT32_TRUNC_CAST)free_index;
        node = active->next;
        if (free_index < node->free_index) {
            do {
                node = node->next;
            }
            while (free_index < node->free_index);

            list_remove(active);
            list_insert(active, node);
        }

        node = pool->active;
    }
    else {
        if ((node = allocator_alloc(pool->allocator, size)) == NULL)
            return -1;

        if (ps->got_a_new_node) {
            active->next = ps->free;
            ps->free = active;
        }

        ps->got_a_new_node = 1;
    }

    memcpy(node->first_avail, active->first_avail, cur_len);

    ps->node = node;
    ps->vbuff.curpos = node->first_avail + cur_len;
    ps->vbuff.endpos = node->endp - 1; /* Save a byte for NUL terminator */

    return 0;
}