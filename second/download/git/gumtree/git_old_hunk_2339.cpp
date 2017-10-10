		return error("corrupt replace bitmap in link extension");
	if (ret != sz)
		return error("garbage at the end of link extension");
	return 0;
}

static int write_strbuf(void *user_data, const void *data, size_t len)
{
	struct strbuf *sb = user_data;
	strbuf_add(sb, data, len);
	return len;
}

int write_link_extension(struct strbuf *sb,
			 struct index_state *istate)
{
	struct split_index *si = istate->split_index;
	strbuf_add(sb, si->base_sha1, 20);
	if (!si->delete_bitmap && !si->replace_bitmap)
		return 0;
	ewah_serialize_to(si->delete_bitmap, write_strbuf, sb);
	ewah_serialize_to(si->replace_bitmap, write_strbuf, sb);
	return 0;
}

static void mark_base_index_entries(struct index_state *base)
{
	int i;
