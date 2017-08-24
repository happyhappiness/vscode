{
			dest->length = wcs - dest->s;
			dest->s[dest->length] = L'\0';
			wcs_length = mbs_length;
			if (NULL == archive_wstring_ensure(dest,
			    dest->length + wcs_length + 1))
				return (-1);
			wcs = dest->s + dest->length;
		}