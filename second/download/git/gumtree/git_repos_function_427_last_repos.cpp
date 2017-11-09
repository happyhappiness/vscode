void oid_array_append(struct oid_array *array, const struct object_id *oid)
{
	ALLOC_GROW(array->oid, array->nr + 1, array->alloc);
	oidcpy(&array->oid[array->nr++], oid);
	array->sorted = 0;
}