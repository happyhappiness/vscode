static void find_internet_password(void)
{
	void *buf;
	UInt32 len;
	SecKeychainItemRef item;

	if (SecKeychainFindInternetPassword(KEYCHAIN_ARGS, &len, &buf, &item))
		return;

	write_item("password", buf, len);
	if (!username)
		find_username_in_item(item);

	SecKeychainItemFreeContent(NULL, buf);
}