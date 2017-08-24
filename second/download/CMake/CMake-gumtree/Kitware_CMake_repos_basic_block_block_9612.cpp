{
		size_t len = 255 & (int)*p;
		char *name;

		strcpy(buff, "user.");
		name = buff + strlen(buff);
		memcpy(name, p + 1, len);
		name[len] = '\0';
		setup_xattr(a, entry, namespace, name, buff, *fd, path);
		p += 1 + len;
	}