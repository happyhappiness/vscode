{
		if (safe_char[*(const unsigned char *)str])
			continue;
		if (start != str)
			archive_strncat(s, start, str - start);
		c = (unsigned char)*str;
		buf[0] = '\\';
		buf[1] = (c / 64) + '0';
		buf[2] = (c / 8 % 8) + '0';
		buf[3] = (c % 8) + '0';
		archive_strncat(s, buf, 4);
		start = str + 1;
	}