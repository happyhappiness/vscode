static inline const unsigned char *tree_entry_extract(struct tree_desc *desc, const char **pathp, unsigned int *modep)
{
	*pathp = desc->entry.path;
	*modep = desc->entry.mode;
	return desc->entry.sha1;
}