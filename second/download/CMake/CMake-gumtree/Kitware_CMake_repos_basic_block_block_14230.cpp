{
			/* The same file already exists. retry with
			 * a new filename. */
			if (GetLastError() == ERROR_FILE_EXISTS)
				continue;
			/* Otherwise, fail creation temporary file. */
			la_dosmaperr(GetLastError());
			goto exit_tmpfile;
		}