{
	struct mtree_writer *mtree = a->format_data;
	struct mtree_entry *me;

	if ((me = mtree->mtree_entry) == NULL)
		return (ARCHIVE_OK);
	mtree->mtree_entry = NULL;

	if (me->reg_info)
		sum_final(mtree, me->reg_info);

	return (ARCHIVE_OK);
}