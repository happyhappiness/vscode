(*str == '\n') {
			if (in_shell)
				archive_strcat(buf, "\"\n\"");
			else
				archive_strcat(buf, "\\n");
			++str;
		}