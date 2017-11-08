unsigned long sizeof_delta_index(struct delta_index *index)
{
	if (index)
		return index->memsize;
	else
		return 0;
}