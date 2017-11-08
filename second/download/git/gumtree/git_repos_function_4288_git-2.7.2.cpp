static int fill_blob_sha1_and_mode(struct origin *origin)
{
	if (!is_null_sha1(origin->blob_sha1))
		return 0;
	if (get_tree_entry(origin->commit->object.oid.hash,
			   origin->path,
			   origin->blob_sha1, &origin->mode))
		goto error_out;
	if (sha1_object_info(origin->blob_sha1, NULL) != OBJ_BLOB)
		goto error_out;
	return 0;
 error_out:
	hashclr(origin->blob_sha1);
	origin->mode = S_IFINVALID;
	return -1;
}