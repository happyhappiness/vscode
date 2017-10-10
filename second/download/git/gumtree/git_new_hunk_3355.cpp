	int peek;

	FILE *f = !strcmp(file, "-") ? stdin : fopen(file, "r");
	int file_done = 0;

	if (!f) {
		error_errno("cannot open mbox %s", file);
		goto out;
	}

	do {
		peek = fgetc(f);
	} while (isspace(peek));
