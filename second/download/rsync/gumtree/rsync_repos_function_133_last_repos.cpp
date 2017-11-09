void restore_iobuf_size(xbuf *out)
{
	if (IOBUF_WAS_REDUCED(out->size)) {
		size_t new_size = IOBUF_RESTORE_SIZE(out->size);
		/* Avoid weird buffer interactions by only outputting this to stderr. */
		if (msgs2stderr && DEBUG_GTE(IO, 4)) {
			const char *name = out == &iobuf.out ? "iobuf.out"
					 : out == &iobuf.msg ? "iobuf.msg"
					 : NULL;
			if (name) {
				rprintf(FINFO, "[%s] restored size of %s (+%d)\n",
					who_am_i(), name, (int)(new_size - out->size));
			}
		}
		out->size = new_size;
	}
}