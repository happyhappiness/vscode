int diffcore_count_changes(struct diff_filespec *src,
			   struct diff_filespec *dst,
			   void **src_count_p,
			   void **dst_count_p,
			   unsigned long delta_limit,
			   unsigned long *src_copied,
			   unsigned long *literal_added)
{
	struct spanhash *s, *d;
	struct spanhash_top *src_count, *dst_count;
	unsigned long sc, la;

	src_count = dst_count = NULL;
	if (src_count_p)
		src_count = *src_count_p;
	if (!src_count) {
		src_count = hash_chars(src);
		if (src_count_p)
			*src_count_p = src_count;
	}
	if (dst_count_p)
		dst_count = *dst_count_p;
	if (!dst_count) {
		dst_count = hash_chars(dst);
		if (dst_count_p)
			*dst_count_p = dst_count;
	}
	sc = la = 0;

	s = src_count->data;
	d = dst_count->data;
	for (;;) {
		unsigned dst_cnt, src_cnt;
		if (!s->cnt)
			break; /* we checked all in src */
		while (d->cnt) {
			if (d->hashval >= s->hashval)
				break;
			la += d->cnt;
			d++;
		}
		src_cnt = s->cnt;
		dst_cnt = 0;
		if (d->cnt && d->hashval == s->hashval) {
			dst_cnt = d->cnt;
			d++;
		}
		if (src_cnt < dst_cnt) {
			la += dst_cnt - src_cnt;
			sc += src_cnt;
		}
		else
			sc += dst_cnt;
		s++;
	}
	while (d->cnt) {
		la += d->cnt;
		d++;
	}

	if (!src_count_p)
		free(src_count);
	if (!dst_count_p)
		free(dst_count);
	*src_copied = sc;
	*literal_added = la;
	return 0;
}