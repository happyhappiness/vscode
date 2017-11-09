static int match_cred(const CREDENTIALW *cred)
{
	LPCWSTR target = cred->TargetName;
	if (wusername && wcscmp(wusername, cred->UserName))
		return 0;

	return match_part(&target, L"git", L":") &&
		match_part(&target, protocol, L"://") &&
		match_part_last(&target, wusername, L"@") &&
		match_part(&target, host, L"/") &&
		match_part(&target, path, L"");
}