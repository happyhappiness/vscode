{
	int i;

	if (t == NULL)
		return;
	archive_wstring_free(&t->path);
	archive_wstring_free(&t->full_path);
	free(t->sparse_list);
	free(t->filesystem_table);
	for (i = 0; i < MAX_OVERLAPPED; i++) {
		if (t->ol[i].buff)
			VirtualFree(t->ol[i].buff, 0, MEM_RELEASE);
		CloseHandle(t->ol[i].ol.hEvent);
	}
	free(t);
}