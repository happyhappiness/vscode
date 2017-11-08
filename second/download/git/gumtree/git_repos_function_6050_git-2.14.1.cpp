static int parse_index_info(char *p, int *mode1, int *mode2,
			    struct object_id *oid1, struct object_id *oid2,
			    char *status)
{
	if (*p != ':')
		return error("expected ':', got '%c'", *p);
	*mode1 = (int)strtol(p + 1, &p, 8);
	if (*p != ' ')
		return error("expected ' ', got '%c'", *p);
	*mode2 = (int)strtol(p + 1, &p, 8);
	if (*p != ' ')
		return error("expected ' ', got '%c'", *p);
	if (get_oid_hex(++p, oid1))
		return error("expected object ID, got '%s'", p + 1);
	p += GIT_SHA1_HEXSZ;
	if (*p != ' ')
		return error("expected ' ', got '%c'", *p);
	if (get_oid_hex(++p, oid2))
		return error("expected object ID, got '%s'", p + 1);
	p += GIT_SHA1_HEXSZ;
	if (*p != ' ')
		return error("expected ' ', got '%c'", *p);
	*status = *++p;
	if (!*status)
		return error("missing status");
	if (p[1] && !isdigit(p[1]))
		return error("unexpected trailer: '%s'", p + 1);
	return 0;
}