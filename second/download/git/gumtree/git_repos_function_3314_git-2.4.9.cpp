static int disambiguate_blob_only(const unsigned char *sha1, void *cb_data_unused)
{
	int kind = sha1_object_info(sha1, NULL);
	return kind == OBJ_BLOB;
}