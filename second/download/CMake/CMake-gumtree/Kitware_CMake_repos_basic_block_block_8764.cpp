{

	if (!ctx->valid)
		return (ARCHIVE_FAILED);

	CryptHashData(ctx->hash,
		      (unsigned char *)(uintptr_t)buf,
		      (DWORD)len, 0);
	return (ARCHIVE_OK);
}