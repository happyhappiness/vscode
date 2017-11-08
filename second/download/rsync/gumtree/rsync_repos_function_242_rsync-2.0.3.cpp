local void flush_pending(strm)
    z_stream *strm;
{
    deflate_state *state = (deflate_state *) strm->state;
    unsigned len = state->pending;

    if (len > strm->avail_out) len = strm->avail_out;
    if (len == 0) return;

    if (strm->next_out != NULL) {
	zmemcpy(strm->next_out, state->pending_out, len);
	strm->next_out += len;
    }
    state->pending_out += len;
    strm->total_out += len;
    strm->avail_out -= len;
    state->pending -= len;
    if (state->pending == 0) {
        state->pending_out = state->pending_buf;
    }
}