static int pack_copy_priority(const char *name)
{
	if (!starts_with(name, "pack"))
		return 0;
	if (ends_with(name, ".keep"))
		return 1;
	if (ends_with(name, ".pack"))
		return 2;
	if (ends_with(name, ".idx"))
		return 3;
	return 4;
}