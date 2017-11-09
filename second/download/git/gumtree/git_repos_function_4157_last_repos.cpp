struct tree *parse_tree_indirect(const struct object_id *oid)
{
	struct object *obj = parse_object(oid);
	do {
		if (!obj)
			return NULL;
		if (obj->type == OBJ_TREE)
			return (struct tree *) obj;
		else if (obj->type == OBJ_COMMIT)
			obj = &(((struct commit *) obj)->tree->object);
		else if (obj->type == OBJ_TAG)
			obj = ((struct tag *) obj)->tagged;
		else
			return NULL;
		if (!obj->parsed)
			parse_object(&obj->oid);
	} while (1);
}