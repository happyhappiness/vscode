static void *get_data_from_pack(struct object_entry *obj)
{
	return unpack_data(obj, NULL, NULL);
}