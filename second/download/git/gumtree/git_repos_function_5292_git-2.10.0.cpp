static int batch_loose_object(const unsigned char *sha1,
			      const char *path,
			      void *data)
{
	sha1_array_append(data, sha1);
	return 0;
}