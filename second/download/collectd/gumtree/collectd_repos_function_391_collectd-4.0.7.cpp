static char *
get_spec_by_uuid(const char *s)
{
	char uuid[16];
	int i;

	if(strlen(s) != 36
	|| s[8] != '-' || s[13] != '-' || s[18] != '-' || s[23] != '-') {
		goto bad_uuid;
	}

	for(i=0; i<16; i++) {
		if(*s == '-') {
			s++;
		}
		if(!isxdigit((int)s[0]) || !isxdigit((int)s[1])) {
			goto bad_uuid;
		}
		uuid[i] = ((fromhex(s[0]) << 4) | fromhex(s[1]));
		s += 2;
	}
	return get_spec_by_x(UUID, uuid);

	bad_uuid:
		DEBUG("Found an invalid UUID: %s", s);
	return NULL;
}