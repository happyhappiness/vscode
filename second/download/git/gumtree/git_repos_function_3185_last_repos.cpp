static void ident_free_fn(struct stream_filter *filter)
{
	struct ident_filter *ident = (struct ident_filter *)filter;
	strbuf_release(&ident->left);
	free(filter);
}