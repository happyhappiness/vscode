int deflateEnd (strm)
    z_stream *strm;
{
    deflate_state *state = (deflate_state *) strm->state;

    if (strm == Z_NULL || state == Z_NULL) return Z_STREAM_ERROR;

    TRY_FREE(strm, state->window, state->w_size * 2 * sizeof(Byte));
    TRY_FREE(strm, state->prev, state->w_size * sizeof(Pos));
    TRY_FREE(strm, state->head, state->hash_size * sizeof(Pos));
    TRY_FREE(strm, state->pending_buf, state->lit_bufsize * 2 * sizeof(ush));

    ZFREE(strm, state, sizeof(deflate_state));
    strm->state = Z_NULL;

    return Z_OK;
}