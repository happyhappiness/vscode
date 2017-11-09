static void add_internet_password(void)
{
	/* Only store complete credentials */
	if (!protocol || !host || !username || !password)
		return;

	if (SecKeychainAddInternetPassword(
	      KEYCHAIN_ARGS,
	      KEYCHAIN_ITEM(password),
	      NULL))
		return;
}