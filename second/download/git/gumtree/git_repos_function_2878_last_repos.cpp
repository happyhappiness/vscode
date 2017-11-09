void add_name_decoration(enum decoration_type type, const char *name, struct object *obj)
{
	struct name_decoration *res;
	FLEX_ALLOC_STR(res, name, name);
	res->type = type;
	res->next = add_decoration(&name_decoration, obj, res);
}