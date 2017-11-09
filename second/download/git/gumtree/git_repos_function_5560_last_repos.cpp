static unsigned check_objects(void)
{
	unsigned i, max, foreign_nr = 0;

	max = get_max_object_index();
	for (i = 0; i < max; i++)
		foreign_nr += check_object(get_indexed_object(i));
	return foreign_nr;
}