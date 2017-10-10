
	default:
		return raise(sig);
	}
}

int link(const char *oldpath, const char *newpath)
{
	typedef BOOL (WINAPI *T)(LPCWSTR, LPCWSTR, LPSECURITY_ATTRIBUTES);
	static T create_hard_link = NULL;
	wchar_t woldpath[MAX_PATH], wnewpath[MAX_PATH];
	if (xutftowcs_path(woldpath, oldpath) < 0 ||
