static int grab_objectname(const char *name, const unsigned char *sha1,
			    struct atom_value *v)
{
	if (!strcmp(name, "objectname")) {
		char *s = xmalloc(41);
		strcpy(s, sha1_to_hex(sha1));
		v->s = s;
		return 1;
	}
	if (!strcmp(name, "objectname:short")) {
		v->s = xstrdup(find_unique_abbrev(sha1, DEFAULT_ABBREV));
		return 1;
	}
	return 0;
}