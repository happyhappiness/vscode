int write_link_extension(struct strbuf *sb,
			 struct index_state *istate)
{
	struct split_index *si = istate->split_index;
	strbuf_add(sb, si->base_sha1, 20);
	if (!si->delete_bitmap && !si->replace_bitmap)
		return 0;
	ewah_serialize_strbuf(si->delete_bitmap, sb);
	ewah_serialize_strbuf(si->replace_bitmap, sb);
	return 0;
}