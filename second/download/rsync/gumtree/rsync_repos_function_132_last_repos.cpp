void reduce_iobuf_size(xbuf *out, size_t new_size)
{
	if (new_size < out->size) {
		/* Avoid weird buffer interactions by only outputting this to stderr. */
		if (msgs2stderr && DEBUG_GTE(IO, 4)) {
			const char *name = out == &iobuf.out ? "iobuf.out"
					 : out == &iobuf.msg ? "iobuf.msg"
					 : NULL;
			if (name) {
				rprintf(FINFO, "[%s] reduced size of %s (-%d)\n",
					who_am_i(), name, (int)(out->size - new_size));
			}
		}
		out->size = new_size;
	}
}