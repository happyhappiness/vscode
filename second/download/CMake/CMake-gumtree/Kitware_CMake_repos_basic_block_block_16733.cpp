{
		/*
		 * If generating format is not classic one(v1), output
		 * a full pathname.
		 */
		mtree_quote(str, me->parentdir.s);
		archive_strappend_char(str, '/');
	}