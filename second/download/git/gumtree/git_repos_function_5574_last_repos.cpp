static int is_delta_type(enum object_type type)
{
	return (type == OBJ_REF_DELTA || type == OBJ_OFS_DELTA);
}