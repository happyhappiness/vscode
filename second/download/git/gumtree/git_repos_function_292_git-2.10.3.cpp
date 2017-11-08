void walker_free(struct walker *walker)
{
	walker->cleanup(walker);
	free(walker);
}