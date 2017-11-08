static int loose_from_alt_odb(struct alternate_object_database *alt,
			      void *vdata)
{
	struct loose_alt_odb_data *data = vdata;
	return for_each_loose_file_in_objdir(alt->base,
					     data->cb, NULL, NULL,
					     data->data);
}