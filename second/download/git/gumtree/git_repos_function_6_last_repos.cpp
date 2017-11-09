int parse_tag_buffer(struct tag *item, const void *data, unsigned long size)
{
	struct object_id oid;
	char type[20];
	const char *bufptr = data;
	const char *tail = bufptr + size;
	const char *nl;

	if (item->object.parsed)
		return 0;
	item->object.parsed = 1;

	if (size < GIT_SHA1_HEXSZ + 24)
		return -1;
	if (memcmp("object ", bufptr, 7) || parse_oid_hex(bufptr + 7, &oid, &bufptr) || *bufptr++ != '\n')
		return -1;

	if (!starts_with(bufptr, "type "))
		return -1;
	bufptr += 5;
	nl = memchr(bufptr, '\n', tail - bufptr);
	if (!nl || sizeof(type) <= (nl - bufptr))
		return -1;
	memcpy(type, bufptr, nl - bufptr);
	type[nl - bufptr] = '\0';
	bufptr = nl + 1;

	if (!strcmp(type, blob_type)) {
		item->tagged = &lookup_blob(&oid)->object;
	} else if (!strcmp(type, tree_type)) {
		item->tagged = &lookup_tree(&oid)->object;
	} else if (!strcmp(type, commit_type)) {
		item->tagged = &lookup_commit(&oid)->object;
	} else if (!strcmp(type, tag_type)) {
		item->tagged = &lookup_tag(&oid)->object;
	} else {
		error("Unknown type %s", type);
		item->tagged = NULL;
	}

	if (bufptr + 4 < tail && starts_with(bufptr, "tag "))
		; 		/* good */
	else
		return -1;
	bufptr += 4;
	nl = memchr(bufptr, '\n', tail - bufptr);
	if (!nl)
		return -1;
	item->tag = xmemdupz(bufptr, nl - bufptr);
	bufptr = nl + 1;

	if (bufptr + 7 < tail && starts_with(bufptr, "tagger "))
		item->date = parse_tag_date(bufptr, tail);
	else
		item->date = 0;

	return 0;
}