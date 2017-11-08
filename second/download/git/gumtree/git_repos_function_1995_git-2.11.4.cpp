struct alternate_object_database *alloc_alt_odb(const char *dir)
{
	struct alternate_object_database *ent;

	FLEX_ALLOC_STR(ent, path, dir);
	strbuf_init(&ent->scratch, 0);
	strbuf_addf(&ent->scratch, "%s/", dir);
	ent->base_len = ent->scratch.len;

	return ent;
}