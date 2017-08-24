{
			fullname = __la_win_permissive_name_w(a->name);
			a->fh = CreateFileW(fullname, GENERIC_WRITE, 0, NULL,
			    CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
		}