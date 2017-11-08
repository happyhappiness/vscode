void oid_array_clear(struct oid_array *array)
{
	free(array->oid);
	array->oid = NULL;
	array->nr = 0;
	array->alloc = 0;
	array->sorted = 0;
}