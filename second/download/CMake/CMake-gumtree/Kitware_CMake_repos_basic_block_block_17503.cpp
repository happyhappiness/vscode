{
		if (*utf8 == '\\')
			*utf8 = '/';
		++utf8;
		--len;
	}