(; *p != '\0'; ++p) {
			if (p[0] == '/' && p[1] != '\0')
				name = p + 1;
		}