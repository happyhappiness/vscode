static int clear_ce_flags(struct cache_entry **cache, int nr,
			    int select_mask, int clear_mask,
			    struct exclude_list *el)
{
	static struct strbuf prefix = STRBUF_INIT;

	strbuf_reset(&prefix);

	return clear_ce_flags_1(cache, nr,
				&prefix,
				select_mask, clear_mask,
				el, 0);
}