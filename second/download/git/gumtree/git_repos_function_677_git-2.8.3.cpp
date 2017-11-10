static int replace_object_pos(const unsigned char *sha1)
{
	return sha1_pos(sha1, replace_object, replace_object_nr,
			replace_sha1_access);
}