				*t++ = toLower(f);
			else
				*t++ = *f;
		} while (*++f != '/' && *f);
		*t++ = '\0';

		add_suffix(&suftree, *buf, buf+1);
	}

	free(buf);
}

