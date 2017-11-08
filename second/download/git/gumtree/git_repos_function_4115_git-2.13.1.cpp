static int disambiguate_blob_only(const struct object_id *oid, void *cb_data_unused)
{
	int kind = sha1_object_info(oid->hash, NULL);
	return kind == OBJ_BLOB;
}