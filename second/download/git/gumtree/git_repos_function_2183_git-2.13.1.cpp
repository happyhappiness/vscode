int for_each_loose_object(each_loose_object_fn cb, void *data, unsigned flags)
{
	struct loose_alt_odb_data alt;
	int r;

	r = for_each_loose_file_in_objdir(get_object_directory(),
					  cb, NULL, NULL, data);
	if (r)
		return r;

	if (flags & FOR_EACH_OBJECT_LOCAL_ONLY)
		return 0;

	alt.cb = cb;
	alt.data = data;
	return foreach_alt_odb(loose_from_alt_odb, &alt);
}