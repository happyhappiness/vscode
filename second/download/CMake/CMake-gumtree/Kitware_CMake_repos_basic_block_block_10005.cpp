{
	if (t->findData)
		return ((t->findData->dwFileAttributes
			        & FILE_ATTRIBUTE_REPARSE_POINT) &&
			(t->findData->dwReserved0
			    == IO_REPARSE_TAG_SYMLINK));
	return (0);
}