static struct git_istream *attach_stream_filter(struct git_istream *st,
						struct stream_filter *filter)
{
	struct git_istream *ifs = xmalloc(sizeof(*ifs));
	struct filtered_istream *fs = &(ifs->u.filtered);

	ifs->vtbl = &filtered_vtbl;
	fs->upstream = st;
	fs->filter = filter;
	fs->i_end = fs->i_ptr = 0;
	fs->o_end = fs->o_ptr = 0;
	fs->input_finished = 0;
	ifs->size = -1; /* unknown */
	return ifs;
}