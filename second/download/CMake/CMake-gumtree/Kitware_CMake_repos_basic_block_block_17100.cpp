((len = strcspn(str, meta)) != 0) {
			archive_strncat(buf, str, len);
			str += len;
		} else if (*str == '\n') {
			if (in_shell)
				archive_strcat(buf, "\"\n\"");
			else
				archive_strcat(buf, "\\n");
			++str;
		} else {
			archive_strappend_char(buf, '\\');
			archive_strappend_char(buf, *str);
			++str;
		}