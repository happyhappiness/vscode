static void load_cred_funcs(void)
{
	/* load DLLs */
	advapi = LoadLibrary("advapi32.dll");
	if (!advapi)
		die("failed to load advapi32.dll");

	/* get function pointers */
	CredWriteW = (CredWriteWT)GetProcAddress(advapi, "CredWriteW");
	CredEnumerateW = (CredEnumerateWT)GetProcAddress(advapi,
	    "CredEnumerateW");
	CredFree = (CredFreeT)GetProcAddress(advapi, "CredFree");
	CredDeleteW = (CredDeleteWT)GetProcAddress(advapi, "CredDeleteW");
	if (!CredWriteW || !CredEnumerateW || !CredFree || !CredDeleteW)
		die("failed to load functions");
}