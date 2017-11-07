static int is_dir_empty(const char *path)
{
	struct strbuf buf = STRBUF_INIT;
	WIN32_FIND_DATAA findbuf;
	HANDLE handle;

	strbuf_addf(&buf, "%s\\*", path);
	handle = FindFirstFileA(buf.buf, &findbuf);
	if (handle == INVALID_HANDLE_VALUE) {
		strbuf_release(&buf);
		return GetLastError() == ERROR_NO_MORE_FILES;
	}

	while (!strcmp(findbuf.cFileName, ".") ||
			!strcmp(findbuf.cFileName, ".."))
		if (!FindNextFile(handle, &findbuf)) {
			strbuf_release(&buf);
			return GetLastError() == ERROR_NO_MORE_FILES;
		}
	FindClose(handle);
	strbuf_release(&buf);
	return 0;
}