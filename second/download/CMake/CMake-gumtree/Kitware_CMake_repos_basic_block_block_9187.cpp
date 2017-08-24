{
		success = CryptGenRandom(hProv, (DWORD)nbytes, (BYTE*)buf);
		CryptReleaseContext(hProv, 0);
		if (success)
			return ARCHIVE_OK;
	}