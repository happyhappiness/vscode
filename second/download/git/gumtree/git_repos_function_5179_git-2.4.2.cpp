static const char *abbrev_ref(const char *name, const char *prefix)
{
	skip_prefix(name, prefix, &name);
	return name;
}