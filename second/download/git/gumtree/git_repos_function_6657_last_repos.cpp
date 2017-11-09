static HANDLE duplicate_handle(HANDLE hnd)
{
	HANDLE hresult, hproc = GetCurrentProcess();
	if (!DuplicateHandle(hproc, hnd, hproc, &hresult, 0, TRUE,
			DUPLICATE_SAME_ACCESS))
		die_lasterr("DuplicateHandle(%li) failed",
			(long) (intptr_t) hnd);
	return hresult;
}