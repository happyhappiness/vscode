static int anonymized_entry_cmp(const void *unused_cmp_data,
				const void *va, const void *vb,
				const void *unused_keydata)
{
	const struct anonymized_entry *a = va, *b = vb;
	return a->orig_len != b->orig_len ||
		memcmp(a->orig, b->orig, a->orig_len);
}