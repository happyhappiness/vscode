static int anonymized_entry_cmp(const void *va, const void *vb,
				const void *data)
{
	const struct anonymized_entry *a = va, *b = vb;
	return a->orig_len != b->orig_len ||
		memcmp(a->orig, b->orig, a->orig_len);
}