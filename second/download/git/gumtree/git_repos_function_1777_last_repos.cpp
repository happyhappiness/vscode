static struct tree_content *dup_tree_content(struct tree_content *s)
{
	struct tree_content *d;
	struct tree_entry *a, *b;
	unsigned int i;

	if (!s)
		return NULL;
	d = new_tree_content(s->entry_count);
	for (i = 0; i < s->entry_count; i++) {
		a = s->entries[i];
		b = new_tree_entry();
		memcpy(b, a, sizeof(*a));
		if (a->tree && is_null_oid(&b->versions[1].oid))
			b->tree = dup_tree_content(a->tree);
		else
			b->tree = NULL;
		d->entries[i] = b;
	}
	d->entry_count = s->entry_count;
	d->delta_depth = s->delta_depth;

	return d;
}