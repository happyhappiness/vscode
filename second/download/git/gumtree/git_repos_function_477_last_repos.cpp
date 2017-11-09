static int fill_blob_sha1_and_mode(struct blame_origin *origin)
{
	if (!is_null_oid(&origin->blob_oid))
		return 0;
	if (get_tree_entry(origin->commit->object.oid.hash,
			   origin->path,
			   origin->blob_oid.hash, &origin->mode))
		goto error_out;
	if (sha1_object_info(origin->blob_oid.hash, NULL) != OBJ_BLOB)
		goto error_out;
	return 0;
 error_out:
	oidclr(&origin->blob_oid);
	origin->mode = S_IFINVALID;
	return -1;
}