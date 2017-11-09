static void mark_alternate_complete(struct object *obj)
{
	mark_complete(&obj->oid);
}