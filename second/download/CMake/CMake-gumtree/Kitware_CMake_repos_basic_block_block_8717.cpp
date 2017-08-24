(*s == '\\') {
			if (s[1] != '\0') {
				archive_strappend_char(as, s[1]);
				s += 2;
			} else
				s++;
		} else if (*s == '"')
			break;
		else {
			archive_strappend_char(as, s[0]);
			s++;
		}