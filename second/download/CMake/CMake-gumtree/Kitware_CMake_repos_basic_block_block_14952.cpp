(l == (size_t)-1) {
			while (*p != '\0') {
				if (*p == '\\')
					*p = '/';
				++p;
			}
			break;
		}