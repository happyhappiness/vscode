static const unsigned char *sha1_access(size_t index, void *table)
{
	struct object_id *array = table;
	return array[index].hash;
}