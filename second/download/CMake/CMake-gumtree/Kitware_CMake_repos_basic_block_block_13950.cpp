{
		int tn = 1;
		if (sc != NULL && (sc->flag & SCONV_TO_UTF16))
			tn = 2;
		if (archive_string_ensure(as, as->length + tn) == NULL)
			return (-1);
		as->s[as->length] = 0;
		if (tn == 2)
			as->s[as->length+1] = 0;
		return (0);
	}