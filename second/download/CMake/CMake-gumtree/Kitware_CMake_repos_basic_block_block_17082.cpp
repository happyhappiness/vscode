(s = in; *s != '\0'; s++) {
		if (*s < 33 || *s > 126 || *s == '%' || *s == '=')
			out_len += 3;
		else
			out_len++;
	}