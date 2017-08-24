{
				r = archive_mstring_get_wcs(a, &ap->name,
				    &wname);
				if (r == 0 && wname != NULL)
					length += wcslen(wname);
				else if (r < 0 && errno == ENOMEM)
					return (0);
				else
					length += sizeof(uid_t) * 3 + 1;
			}