static int batch_object_cb(const unsigned char sha1[20], void *vdata)
{
	struct object_cb_data *data = vdata;
	hashcpy(data->expand->oid.hash, sha1);
	batch_object_write(NULL, data->opt, data->expand);
	return 0;
}