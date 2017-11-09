static void reverse_patches(struct patch *p)
{
	for (; p; p = p->next) {
		struct fragment *frag = p->fragments;

		SWAP(p->new_name, p->old_name);
		SWAP(p->new_mode, p->old_mode);
		SWAP(p->is_new, p->is_delete);
		SWAP(p->lines_added, p->lines_deleted);
		SWAP(p->old_sha1_prefix, p->new_sha1_prefix);

		for (; frag; frag = frag->next) {
			SWAP(frag->newpos, frag->oldpos);
			SWAP(frag->newlines, frag->oldlines);
		}
	}
}