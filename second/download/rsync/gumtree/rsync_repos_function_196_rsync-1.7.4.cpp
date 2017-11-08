local ulg ct_flush_block(s, buf, stored_len, flush)
    deflate_state *s;
    charf *buf;       /* input block, or NULL if too old */
    ulg stored_len;   /* length of input block */
    int flush;        /* Z_FINISH if this is the last block for a file */
{
    ulg opt_lenb, static_lenb; /* opt_len and static_len in bytes */
    int max_blindex;  /* index of last bit length code of non zero freq */
    int eof = flush == Z_FINISH;

    ++s->blocks_in_packet;

    /* Check if the file is ascii or binary */
    if (s->data_type == UNKNOWN) set_data_type(s);

    /* Construct the literal and distance trees */
    build_tree(s, (tree_desc *)(&(s->l_desc)));
    Tracev((stderr, "\nlit data: dyn %ld, stat %ld", s->opt_len,
            s->static_len));

    build_tree(s, (tree_desc *)(&(s->d_desc)));
    Tracev((stderr, "\ndist data: dyn %ld, stat %ld", s->opt_len,
            s->static_len));
    /* At this point, opt_len and static_len are the total bit lengths of
     * the compressed block data, excluding the tree representations.
     */

    /* Build the bit length tree for the above two trees, and get the index
     * in bl_order of the last bit length code to send.
     */
    max_blindex = build_bl_tree(s);

    /* Determine the best encoding. Compute first the block length in bytes */
    opt_lenb = (s->opt_len+3+7)>>3;
    static_lenb = (s->static_len+3+7)>>3;

    Tracev((stderr, "\nopt %lu(%lu) stat %lu(%lu) stored %lu lit %u ",
            opt_lenb, s->opt_len, static_lenb, s->static_len, stored_len,
            s->last_lit));

    if (static_lenb <= opt_lenb) opt_lenb = static_lenb;

    /* If compression failed and this is the first and last block,
     * and if the .zip file can be seeked (to rewrite the local header),
     * the whole file is transformed into a stored file:
     */
#ifdef STORED_FILE_OK
#  ifdef FORCE_STORED_FILE
    if (eof && compressed_len == 0L) /* force stored file */
#  else
    if (stored_len <= opt_lenb && eof && s->compressed_len==0L && seekable())
#  endif
    {
        /* Since LIT_BUFSIZE <= 2*WSIZE, the input data must be there: */
        if (buf == (charf*)0) error ("block vanished");

        copy_block(buf, (unsigned)stored_len, 0); /* without header */
        s->compressed_len = stored_len << 3;
        s->method = STORED;
    } else
#endif /* STORED_FILE_OK */

#ifdef FORCE_STORED
    if (buf != (char*)0) /* force stored block */
#else
    if (stored_len+4 <= opt_lenb && buf != (char*)0)
                       /* 4: two words for the lengths */
#endif
    {
        /* The test buf != NULL is only necessary if LIT_BUFSIZE > WSIZE.
         * Otherwise we can't have processed more than WSIZE input bytes since
         * the last block flush, because compression would have been
         * successful. If LIT_BUFSIZE <= WSIZE, it is never too late to
         * transform a block into a stored block.
         */
        ct_stored_block(s, buf, stored_len, eof);
    } else

#ifdef FORCE_STATIC
    if (static_lenb >= 0) /* force static trees */
#else
    if (static_lenb == opt_lenb)
#endif
    {
        send_bits(s, (STATIC_TREES<<1)+eof, 3);
        compress_block(s, (ct_data *)static_ltree, (ct_data *)static_dtree);
        s->compressed_len += 3 + s->static_len;
    } else {
        send_bits(s, (DYN_TREES<<1)+eof, 3);
        send_all_trees(s, s->l_desc.max_code+1, s->d_desc.max_code+1,
                       max_blindex+1);
        compress_block(s, (ct_data *)s->dyn_ltree, (ct_data *)s->dyn_dtree);
        s->compressed_len += 3 + s->opt_len;
    }
    Assert (s->compressed_len == s->bits_sent, "bad compressed size");
    init_block(s);

    if (eof) {
        bi_windup(s);
        s->compressed_len += 7;  /* align on byte boundary */
    }
    Tracev((stderr,"\ncomprlen %lu(%lu) ", s->compressed_len>>3,
           s->compressed_len-7*eof));

    return s->compressed_len >> 3;
}