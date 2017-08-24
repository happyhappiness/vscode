{
		algname = getalgname(sum->alg);
		algsize = getalgsize(sum->alg);
		if (algname != NULL) {
			const char *hex = "0123456789abcdef";
			p = buff;
			s = sum->val;
			for (i = 0; i < algsize; i++) {
				*p++ = hex[(*s >> 4)];
				*p++ = hex[(*s & 0x0f)];
				s++;
			}
			*p = '\0';
			r = xmlwrite_string_attr(a, writer,
			    key, buff,
			    "style", algname);
			if (r < 0)
				return (ARCHIVE_FATAL);
		}
	}