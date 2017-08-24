(l = 0, i = 0;  acmd->argv[i] != NULL; i++) {
		if (i == 0)
			continue;
		l += (int)strlen(acmd->argv[i]) + 1;
	}