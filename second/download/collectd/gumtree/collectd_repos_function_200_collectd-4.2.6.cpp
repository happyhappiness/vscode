static signed long long dict_get_value (CFDictionaryRef dict, const char *key)
{
	signed long long val_int;
	CFNumberRef      val_obj;
	CFStringRef      key_obj;

	/* `key_obj' needs to be released. */
	key_obj = CFStringCreateWithCString (kCFAllocatorDefault, key,
		       	kCFStringEncodingASCII);
	if (key_obj == NULL)
	{
		DEBUG ("CFStringCreateWithCString (%s) failed.", key);
		return (-1LL);
	}
	
	/* get => we don't need to release (== free) the object */
	val_obj = (CFNumberRef) CFDictionaryGetValue (dict, key_obj);

	CFRelease (key_obj);

	if (val_obj == NULL)
	{
		DEBUG ("CFDictionaryGetValue (%s) failed.", key);
		return (-1LL);
	}

	if (!CFNumberGetValue (val_obj, kCFNumberSInt64Type, &val_int))
	{
		DEBUG ("CFNumberGetValue (%s) failed.", key);
		return (-1LL);
	}

	return (val_int);
}