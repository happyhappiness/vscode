const char *rerere_path(const struct rerere_id *id, const char *file)
{
	if (!file)
		return git_path("rr-cache/%s", rerere_id_hex(id));

	if (id->variant <= 0)
		return git_path("rr-cache/%s/%s", rerere_id_hex(id), file);

	return git_path("rr-cache/%s/%s.%d",
			rerere_id_hex(id), file, id->variant);
}