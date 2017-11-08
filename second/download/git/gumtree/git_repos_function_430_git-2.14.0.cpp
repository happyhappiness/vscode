void oid_array_clear(struct oid_array *array)
{
	FREE_AND_NULL(array->oid);
	array->nr = 0;
	array->alloc = 0;
	array->sorted = 0;
}