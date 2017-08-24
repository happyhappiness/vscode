((tm.tm_hour = strtoi_lim(s, &s, 0, 23)) < 0 || *s++ != ':') {
		goto out;
	}