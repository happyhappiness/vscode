{
			if (*wp > 255) {
				*p++ = '?';
				wp++;
				defchar_used = 1;
			} else
				*p++ = (char)*wp++;
			count++;
		}