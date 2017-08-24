(!CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL,
		CRYPT_VERIFYCONTEXT)) {
		la_dosmaperr(GetLastError());
		goto exit_tmpfile;
	}