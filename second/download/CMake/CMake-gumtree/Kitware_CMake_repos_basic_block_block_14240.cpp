{
		size_t l;
		wchar_t *tmp;

		l = GetTempPathW(0, NULL);
		if (l == 0) {
			la_dosmaperr(GetLastError());
			goto exit_tmpfile;
		}
		tmp = malloc(l*sizeof(wchar_t));
		if (tmp == NULL) {
			errno = ENOMEM;
			goto exit_tmpfile;
		}
		GetTempPathW((DWORD)l, tmp);
		archive_wstrcpy(&temp_name, tmp);
		free(tmp);
	}