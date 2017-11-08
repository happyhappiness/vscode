static int batch_packed_object(const unsigned char *sha1,
			       struct packed_git *pack,
			       uint32_t pos,
			       void *data)
{
	sha1_array_append(data, sha1);
	return 0;
}