static int mark_packed_for_connectivity(const unsigned char *sha1,
					struct packed_git *pack,
					uint32_t pos,
					void *data)
{
	mark_object_for_connectivity(sha1);
	return 0;
}