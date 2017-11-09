static void add_unreachable_loose_objects(void)
{
	for_each_loose_file_in_objdir(get_object_directory(),
				      add_loose_object,
				      NULL, NULL, NULL);
}