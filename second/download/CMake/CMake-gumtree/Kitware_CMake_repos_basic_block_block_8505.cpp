(name != NULL  &&  *name != L'\0' && len > 0)
		archive_mstring_copy_wcs_len(&ap->name, name, len);
	else
		archive_mstring_clean(&ap->name)