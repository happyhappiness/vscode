static char *
get_spec_by_x(int n, const char *t)
{
	struct uuidCache_s *uc;

	uuidcache_init();
	uc = uuidCache;

	while(uc) {
		switch(n) {
		case UUID:
			if(!memcmp(t, uc->uuid, sizeof(uc->uuid))) {
				return sstrdup(uc->device);
			}
			break;
		case VOL:
			if(!strcmp(t, uc->label)) {
				return sstrdup(uc->device);
			}
			break;
		}
		uc = uc->next;
	}
	return NULL;
}