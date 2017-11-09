static void record_recent_object(struct object *obj,
				 const char *name,
				 void *data)
{
	oid_array_append(&recent_objects, &obj->oid);
}