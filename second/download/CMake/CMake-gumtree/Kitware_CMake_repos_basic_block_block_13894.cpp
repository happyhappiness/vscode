(strcmp(tc, "UTF-8") == 0)
		flag |= SCONV_TO_UTF8;
	else if (strcmp(tc, "UTF-16BE") == 0)
		flag |= SCONV_TO_UTF16BE;
	else if (strcmp(tc, "UTF-16LE") == 0)
		flag |= SCONV_TO_UTF16LE