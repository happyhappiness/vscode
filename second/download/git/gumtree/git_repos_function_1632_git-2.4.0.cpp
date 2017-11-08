static int retry_bad_packed_offset(struct packed_git *p, off_t obj_offset)
{
	int type;
	struct revindex_entry *revidx;
	const unsigned char *sha1;
	revidx = find_pack_revindex(p, obj_offset);
	if (!revidx)
		return OBJ_BAD;
	sha1 = nth_packed_object_sha1(p, revidx->nr);
	mark_bad_packed_object(p, sha1);
	type = sha1_object_info(sha1, NULL);
	if (type <= OBJ_NONE)
		return OBJ_BAD;
	return type;
}