static const unsigned char *sha1_access(size_t index, void *table)
{
	unsigned char (*array)[20] = table;
	return array[index];
}