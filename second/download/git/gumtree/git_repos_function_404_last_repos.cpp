void move_index_extensions(struct index_state *dst, struct index_state *src)
{
	dst->untracked = src->untracked;
	src->untracked = NULL;
}