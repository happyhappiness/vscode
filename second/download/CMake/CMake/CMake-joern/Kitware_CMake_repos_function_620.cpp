static void *
la_GetFunctionKernel32(const char *name)
{
	static HINSTANCE lib;
	static int set;
	if (!set) {
		set = 1;
		lib = LoadLibrary(TEXT("kernel32.dll"));
	}
	if (lib == NULL) {
		fprintf(stderr, "Can't load kernel32.dll?!\n");
		exit(1);
	}
	return (void *)GetProcAddress(lib, name);
}