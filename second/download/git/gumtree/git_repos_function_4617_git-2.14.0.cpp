static void insert_one_alternate_object(struct object *obj)
{
	rev_list_insert_ref(NULL, &obj->oid);
}