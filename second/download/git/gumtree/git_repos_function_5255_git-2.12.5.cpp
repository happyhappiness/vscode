static int mark_loose_for_connectivity(const unsigned char *sha1,
				       const char *path,
				       void *data)
{
	mark_object_for_connectivity(sha1);
	return 0;
}