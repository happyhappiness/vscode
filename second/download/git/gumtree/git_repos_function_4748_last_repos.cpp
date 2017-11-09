static int write_each_non_note_until(const char *note_path,
		struct write_each_note_data *d)
{
	struct non_note *n = d->next_non_note;
	int cmp = 0, ret;
	while (n && (!note_path || (cmp = strcmp(n->path, note_path)) <= 0)) {
		if (note_path && cmp == 0)
			; /* do nothing, prefer note to non-note */
		else {
			ret = write_each_note_helper(d->root, n->path, n->mode,
						     &n->oid);
			if (ret)
				return ret;
		}
		n = n->next;
	}
	d->next_non_note = n;
	return 0;
}