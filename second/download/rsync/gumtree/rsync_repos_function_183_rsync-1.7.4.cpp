local void ct_init(s)
    deflate_state *s;
{
    if (static_dtree[0].Len == 0) {
        ct_static_init();              /* To do: at compile time */
    }

    s->compressed_len = 0L;

    s->l_desc.dyn_tree = s->dyn_ltree;
    s->l_desc.stat_desc = &static_l_desc;

    s->d_desc.dyn_tree = s->dyn_dtree;
    s->d_desc.stat_desc = &static_d_desc;

    s->bl_desc.dyn_tree = s->bl_tree;
    s->bl_desc.stat_desc = &static_bl_desc;

    s->bi_buf = 0;
    s->bi_valid = 0;
    s->last_eob_len = 8; /* enough lookahead for inflate */
#ifdef DEBUG_ZLIB
    s->bits_sent = 0L;
#endif
    s->blocks_in_packet = 0;

    /* Initialize the first block of the first file: */
    init_block(s);
}