void show_object_with_name(FILE *out, struct object *obj,
			   const struct name_path *path, const char *component)
{
	struct name_path leaf;
	leaf.up = (struct name_path *)path;
	leaf.elem = component;
	leaf.elem_len = strlen(component);

	fprintf(out, "%s ", oid_to_hex(&obj->oid));
	show_path_truncated(out, &leaf);
	fputc('\n', out);
}