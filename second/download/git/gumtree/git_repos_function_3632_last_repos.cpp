char *join_sha1_array_hex(struct oid_array *array, char delim)
{
	struct strbuf joined_hexs = STRBUF_INIT;
	int i;

	for (i = 0; i < array->nr; i++) {
		strbuf_addstr(&joined_hexs, oid_to_hex(array->oid + i));
		if (i + 1 < array->nr)
			strbuf_addch(&joined_hexs, delim);
	}

	return strbuf_detach(&joined_hexs, NULL);
}