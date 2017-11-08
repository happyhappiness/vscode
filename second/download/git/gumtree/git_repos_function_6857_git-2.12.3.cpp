static void find_username_in_item(SecKeychainItemRef item)
{
	SecKeychainAttributeList list;
	SecKeychainAttribute attr;

	list.count = 1;
	list.attr = &attr;
	attr.tag = kSecAccountItemAttr;

	if (SecKeychainItemCopyContent(item, NULL, &list, NULL, NULL))
		return;

	write_item("username", attr.data, attr.length);
	SecKeychainItemFreeContent(&list, NULL);
}