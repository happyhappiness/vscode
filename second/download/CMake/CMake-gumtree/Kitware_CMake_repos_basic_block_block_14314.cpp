(ret >= 0) {
		char *p;

		copy_stat(st, &u);
		p = strrchr(path, '.');
		if (p != NULL && strlen(p) == 4) {
			char exttype[4];

			++ p;
			exttype[0] = toupper(*p++);
			exttype[1] = toupper(*p++);
			exttype[2] = toupper(*p++);
			exttype[3] = '\0';
			if (!strcmp(exttype, "EXE") || !strcmp(exttype, "CMD") ||
				!strcmp(exttype, "BAT") || !strcmp(exttype, "COM"))
				st->st_mode |= S_IXUSR | S_IXGRP | S_IXOTH;
		}
	}