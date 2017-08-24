{
		const char *saved_p = p;

		if (*p != '%') {
			archive_strappend_char(as, *p);
			continue;
		}

		p++;

		long_flag = '\0';
		switch(*p) {
		case 'j':
		case 'l':
		case 'z':
			long_flag = *p;
			p++;
			break;
		}

		switch (*p) {
		case '%':
			archive_strappend_char(as, '%');
			break;
		case 'c':
			s = va_arg(ap, int);
			archive_strappend_char(as, (char)s);
			break;
		case 'd':
			switch(long_flag) {
			case 'j': s = va_arg(ap, intmax_t); break;
			case 'l': s = va_arg(ap, long); break;
			case 'z': s = va_arg(ap, ssize_t); break;
			default:  s = va_arg(ap, int); break;
			}
		        append_int(as, s, 10);
			break;
		case 's':
			switch(long_flag) {
			case 'l':
				pw = va_arg(ap, wchar_t *);
				if (pw == NULL)
					pw = L"(null)";
				if (archive_string_append_from_wcs(as, pw,
				    wcslen(pw)) != 0 && errno == ENOMEM)
					__archive_errx(1, "Out of memory");
				break;
			default:
				p2 = va_arg(ap, char *);
				if (p2 == NULL)
					p2 = "(null)";
				archive_strcat(as, p2);
				break;
			}
			break;
		case 'S':
			pw = va_arg(ap, wchar_t *);
			if (pw == NULL)
				pw = L"(null)";
			if (archive_string_append_from_wcs(as, pw,
			    wcslen(pw)) != 0 && errno == ENOMEM)
				__archive_errx(1, "Out of memory");
			break;
		case 'o': case 'u': case 'x': case 'X':
			/* Common handling for unsigned integer formats. */
			switch(long_flag) {
			case 'j': u = va_arg(ap, uintmax_t); break;
			case 'l': u = va_arg(ap, unsigned long); break;
			case 'z': u = va_arg(ap, size_t); break;
			default:  u = va_arg(ap, unsigned int); break;
			}
			/* Format it in the correct base. */
			switch (*p) {
			case 'o': append_uint(as, u, 8); break;
			case 'u': append_uint(as, u, 10); break;
			default: append_uint(as, u, 16); break;
			}
			break;
		default:
			/* Rewind and print the initial '%' literally. */
			p = saved_p;
			archive_strappend_char(as, *p);
		}
	}