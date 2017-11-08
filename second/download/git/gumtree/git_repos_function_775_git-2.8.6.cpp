void append_merge_tag_headers(struct commit_list *parents,
			      struct commit_extra_header ***tail)
{
	while (parents) {
		struct commit *parent = parents->item;
		handle_signed_tag(parent, tail);
		parents = parents->next;
	}
}