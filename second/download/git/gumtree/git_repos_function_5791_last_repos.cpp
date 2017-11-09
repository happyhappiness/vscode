static int batch_object_cb(const struct object_id *oid, void *vdata)
{
	struct object_cb_data *data = vdata;
	oidcpy(&data->expand->oid, oid);
	batch_object_write(NULL, data->opt, data->expand);
	return 0;
}