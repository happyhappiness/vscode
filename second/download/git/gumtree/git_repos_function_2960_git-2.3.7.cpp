int read_link_extension(struct index_state *istate,
			 const void *data_, unsigned long sz)
{
	const unsigned char *data = data_;
	struct split_index *si;
	int ret;

	if (sz < 20)
		return error("corrupt link extension (too short)");
	si = init_split_index(istate);
	hashcpy(si->base_sha1, data);
	data += 20;
	sz -= 20;
	if (!sz)
		return 0;
	si->delete_bitmap = ewah_new();
	ret = ewah_read_mmap(si->delete_bitmap, data, sz);
	if (ret < 0)
		return error("corrupt delete bitmap in link extension");
	data += ret;
	sz -= ret;
	si->replace_bitmap = ewah_new();
	ret = ewah_read_mmap(si->replace_bitmap, data, sz);
	if (ret < 0)
		return error("corrupt replace bitmap in link extension");
	if (ret != sz)
		return error("garbage at the end of link extension");
	return 0;
}