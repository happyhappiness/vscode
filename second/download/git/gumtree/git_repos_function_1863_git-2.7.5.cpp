static int loose_from_alt_odb(struct alternate_object_database *alt,
			      void *vdata)
{
	struct loose_alt_odb_data *data = vdata;
	struct strbuf buf = STRBUF_INIT;
	int r;

	/* copy base not including trailing '/' */
	strbuf_add(&buf, alt->base, alt->name - alt->base - 1);
	r = for_each_loose_file_in_objdir_buf(&buf,
					      data->cb, NULL, NULL,
					      data->data);
	strbuf_release(&buf);
	return r;
}