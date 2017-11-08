int deflate (strm, flush)
    z_stream *strm;
    int flush;
{
    deflate_state *state = (deflate_state *) strm->state;

    if (strm == Z_NULL || state == Z_NULL) return Z_STREAM_ERROR;
    
    if (strm->next_in == Z_NULL && strm->avail_in != 0) {
        ERR_RETURN(strm, Z_STREAM_ERROR);
    }
    if (strm->avail_out == 0) ERR_RETURN(strm, Z_BUF_ERROR);

    state->strm = strm; /* just in case */

    /* Write the zlib header */
    if (state->status == INIT_STATE) {

        uInt header = (DEFLATED + ((state->w_bits-8)<<4)) << 8;
        uInt level_flags = (state->level-1) >> 1;

        if (level_flags > 3) level_flags = 3;
        header |= (level_flags << 6);
        header += 31 - (header % 31);

        state->status = BUSY_STATE;
        putShortMSB(state, header);
    }

    /* Flush as much pending output as possible */
    if (state->pending != 0) {
        flush_pending(strm);
        if (strm->avail_out == 0) return Z_OK;
    }

    /* If we came back in here to get the last output from
     * a previous flush, we're done for now.
     */
    if (state->status == FLUSH_STATE) {
	state->status = BUSY_STATE;
	if (flush != Z_NO_FLUSH && flush != Z_FINISH)
	    return Z_OK;
    }

    /* User must not provide more input after the first FINISH: */
    if (state->status == FINISH_STATE && strm->avail_in != 0) {
        ERR_RETURN(strm, Z_BUF_ERROR);
    }

    /* Start a new block or continue the current one.
     */
    if (strm->avail_in != 0 || state->lookahead != 0 ||
        (flush == Z_FINISH && state->status != FINISH_STATE)) {
        int quit;

        if (flush == Z_FINISH) {
            state->status = FINISH_STATE;
        }
        if (state->level <= 3) {
            quit = deflate_fast(state, flush);
        } else {
            quit = deflate_slow(state, flush);
        }
        if (quit || strm->avail_out == 0)
	    return Z_OK;
        /* If flush != Z_NO_FLUSH && avail_out == 0, the next call
         * of deflate should use the same flush parameter to make sure
         * that the flush is complete. So we don't have to output an
         * empty block here, this will be done at next call. This also
         * ensures that for a very small output buffer, we emit at most
         * one empty block.
         */
    }

    /* If a flush was requested, we have a little more to output now. */
    if (flush != Z_NO_FLUSH && flush != Z_FINISH
	&& state->status != FINISH_STATE) {
	switch (flush) {
	case Z_PARTIAL_FLUSH:
	    ct_align(state);
	    break;
	case Z_PACKET_FLUSH:
	    /* Output just the 3-bit `stored' block type value,
	       but not a zero length. */
	    ct_stored_type_only(state);
	    break;
	default:
	    ct_stored_block(state, (char*)0, 0L, 0);
	    /* For a full flush, this empty block will be recognized
	     * as a special marker by inflate_sync().
	     */
	    if (flush == Z_FULL_FLUSH) {
		CLEAR_HASH(state);             /* forget history */
	    }
	}
	flush_pending(strm);
	if (strm->avail_out == 0) {
	    /* We'll have to come back to get the rest of the output;
	     * this ensures we don't output a second zero-length stored
	     * block (or whatever).
	     */
	    state->status = FLUSH_STATE;
	    return Z_OK;
	}
    }

    Assert(strm->avail_out > 0, "bug2");

    if (flush != Z_FINISH) return Z_OK;
    if (state->noheader) return Z_STREAM_END;

    /* Write the zlib trailer (adler32) */
    putShortMSB(state, (uInt)(state->adler >> 16));
    putShortMSB(state, (uInt)(state->adler & 0xffff));
    flush_pending(strm);
    /* If avail_out is zero, the application will call deflate again
     * to flush the rest.
     */
    state->noheader = -1; /* write the trailer only once! */
    return state->pending != 0 ? Z_OK : Z_STREAM_END;
}