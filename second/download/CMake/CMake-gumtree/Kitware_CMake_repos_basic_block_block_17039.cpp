{
		/* Note: assume insert does not have leading or trailing '/' */
		strcpy(p, insert);
		p += strlen(insert);
		*p++ = '/';
	}