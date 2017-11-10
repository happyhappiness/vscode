static void reverse_patches(struct patch *p)
{
	for (; p; p = p->next) {
		struct fragment *frag = p->fragments;

		swap(p->new_name, p->old_name);
		swap(p->new_mode, p->old_mode);
		swap(p->is_new, p->is_delete);
		swap(p->lines_added, p->lines_deleted);
		swap(p->old_sha1_prefix, p->new_sha1_prefix);

		for (; frag; frag = frag->next) {
			swap(frag->newpos, frag->oldpos);
			swap(frag->newlines, frag->oldlines);
		}
	}
}