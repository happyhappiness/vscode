		len = ep - cp;
	if (!e) {
		if (*cp == '-' || *cp == '!') {
			cp++;
			len--;
		}
		if (invalid_attr_name(cp, len)) {
			fprintf(stderr,
				"%.*s is not a valid attribute name: %s:%d\n",
				len, cp, src, lineno);
			return NULL;
		}
	} else {
		if (*cp == '-' || *cp == '!') {
			e->setto = (*cp == '-') ? ATTR__FALSE : ATTR__UNSET;
			cp++;
			len--;
		}
		else if (!equals)
