static int
setup_current_filesystem(struct archive_read_disk *a)
{
	struct tree *t = a->tree;
	wchar_t vol[256];
	wchar_t *path;

	t->current_filesystem->synthetic = -1;/* Not supported */
	path = safe_path_for_statfs(t);
	if (!GetVolumePathNameW(path, vol, sizeof(vol)/sizeof(vol[0]))) {
		free(path);
		t->current_filesystem->remote = -1;
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
                        "GetVolumePathName failed: %d", (int)GetLastError());
		return (ARCHIVE_FAILED);
	}
	free(path);
	switch (GetDriveTypeW(vol)) {
	case DRIVE_UNKNOWN:
	case DRIVE_NO_ROOT_DIR:
		t->current_filesystem->remote = -1;
		break;
	case DRIVE_REMOTE:
		t->current_filesystem->remote = 1;
		break;
	default:
		t->current_filesystem->remote = 0;
		break;
	}

	return (ARCHIVE_OK);
}