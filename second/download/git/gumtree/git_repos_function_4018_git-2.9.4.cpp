static inline const struct object_id *tree_entry_extract(struct tree_desc *desc, const char **pathp, unsigned int *modep)
{
	*pathp = desc->entry.path;
	*modep = desc->entry.mode;
	return desc->entry.oid;
}