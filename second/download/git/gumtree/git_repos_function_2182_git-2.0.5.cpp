static void ident_drain(struct ident_filter *ident, char **output_p, size_t *osize_p)
{
	size_t to_drain = ident->left.len;

	if (*osize_p < to_drain)
		to_drain = *osize_p;
	if (to_drain) {
		memcpy(*output_p, ident->left.buf, to_drain);
		strbuf_remove(&ident->left, 0, to_drain);
		*output_p += to_drain;
		*osize_p -= to_drain;
	}
	if (!ident->left.len)
		ident->state = 0;
}