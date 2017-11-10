static void delete_internet_password(void)
{
	SecKeychainItemRef item;

	/*
	 * Require at least a protocol and host for removal, which is what git
	 * will give us; if you want to do something more fancy, use the
	 * Keychain manager.
	 */
	if (!protocol || !host)
		return;

	if (SecKeychainFindInternetPassword(KEYCHAIN_ARGS, 0, NULL, &item))
		return;

	SecKeychainItemDelete(item);
}