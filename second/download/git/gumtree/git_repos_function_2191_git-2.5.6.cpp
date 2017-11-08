const struct name_decoration *get_name_decoration(const struct object *obj)
{
	return lookup_decoration(&name_decoration, obj);
}