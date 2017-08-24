(GetLastError() != ERROR_FILE_NOT_FOUND) {
			la_dosmaperr(GetLastError());
			goto exit_tmpfile;
		}