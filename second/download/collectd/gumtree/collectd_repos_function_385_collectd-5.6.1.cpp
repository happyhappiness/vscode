static double dict_get_double (CFDictionaryRef dict, const char *key_string) /* {{{ */
{
	double      val_double;
	long long   val_int;
	CFNumberRef val_obj;
	CFStringRef key_obj;

	key_obj = CFStringCreateWithCString (kCFAllocatorDefault, key_string,
			kCFStringEncodingASCII);
	if (key_obj == NULL)
	{
		DEBUG ("CFStringCreateWithCString (%s) failed.\n", key_string);
		return (NAN);
	}

	if ((val_obj = CFDictionaryGetValue (dict, key_obj)) == NULL)
	{
		DEBUG ("CFDictionaryGetValue (%s) failed.", key_string);
		CFRelease (key_obj);
		return (NAN);
	}
	CFRelease (key_obj);

	if (CFGetTypeID (val_obj) == CFNumberGetTypeID ())
	{
		if (CFNumberIsFloatType (val_obj))
		{
			CFNumberGetValue (val_obj,
					kCFNumberDoubleType,
					&val_double);
		}
		else
		{
			CFNumberGetValue (val_obj,
					kCFNumberLongLongType,
					&val_int);
			val_double = val_int;
		}
	}
	else
	{
		DEBUG ("CFGetTypeID (val_obj) = %i", (int) CFGetTypeID (val_obj));
		return (NAN);
	}

	return (val_double);
}