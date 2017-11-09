void register_archiver(struct archiver *ar)
{
	ALLOC_GROW(archivers, nr_archivers + 1, alloc_archivers);
	archivers[nr_archivers++] = ar;
}