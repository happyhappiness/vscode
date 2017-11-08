static inline void finddata2dirent(struct dirent *ent, WIN32_FIND_DATAW *fdata)
{
	/* convert UTF-16 name to UTF-8 */
	xwcstoutf(ent->d_name, fdata->cFileName, sizeof(ent->d_name));

	/* Set file type, based on WIN32_FIND_DATA */
	if (fdata->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		ent->d_type = DT_DIR;
	else
		ent->d_type = DT_REG;
}