struct git_istream *open_istream(const unsigned char *sha1,
				 enum object_type *type,
				 unsigned long *size,
				 struct stream_filter *filter)
{
	struct git_istream *st;
	struct object_info oi = {NULL};
	const unsigned char *real = lookup_replace_object(sha1);
	enum input_source src = istream_source(real, type, &oi);

	if (src < 0)
		return NULL;

	st = xmalloc(sizeof(*st));
	if (open_istream_tbl[src](st, &oi, real, type)) {
		if (open_istream_incore(st, &oi, real, type)) {
			free(st);
			return NULL;
		}
	}
	if (filter) {
		/* Add "&& !is_null_stream_filter(filter)" for performance */
		struct git_istream *nst = attach_stream_filter(st, filter);
		if (!nst) {
			close_istream(st);
			return NULL;
		}
		st = nst;
	}

	*size = st->size;
	return st;
}