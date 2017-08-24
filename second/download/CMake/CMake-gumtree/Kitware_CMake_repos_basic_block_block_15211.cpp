{
			/* Remove multiple directories such as "a/../b../c" */
			archive_wstrcpy(&(a->_name_data), full);
			a->name = a->_name_data.s;
			free(full);
			en = create_filesystem_object(a);
		}