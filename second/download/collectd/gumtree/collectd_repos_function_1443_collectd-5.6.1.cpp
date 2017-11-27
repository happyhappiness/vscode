char *
cu_mount_getoptionvalue(char *line, const char *keyword)
{
	char *r;

	r = cu_mount_checkoption(line, keyword, 0);
	if(r != NULL) {
		char *p;
		r += strlen(keyword);
		p = strchr(r, ',');
		if(p == NULL) {
			return sstrdup(r);
		} else {
			char *m;
			if((p-r) == 1) {
				return NULL;
			}
			m = smalloc(p-r+1);
			sstrncpy(m, r, p-r+1);
			return m;
		}
	}
	return r;
}