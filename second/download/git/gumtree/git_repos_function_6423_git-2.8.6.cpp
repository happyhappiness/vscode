static void store_credential(void)
{
	CREDENTIALW cred;

	if (!wusername || !password)
		return;

	cred.Flags = 0;
	cred.Type = CRED_TYPE_GENERIC;
	cred.TargetName = target;
	cred.Comment = L"saved by git-credential-wincred";
	cred.CredentialBlobSize = (wcslen(password)) * sizeof(WCHAR);
	cred.CredentialBlob = (LPVOID)password;
	cred.Persist = CRED_PERSIST_LOCAL_MACHINE;
	cred.AttributeCount = 0;
	cred.Attributes = NULL;
	cred.TargetAlias = NULL;
	cred.UserName = wusername;

	if (!CredWriteW(&cred, 0))
		die("CredWrite failed");
}