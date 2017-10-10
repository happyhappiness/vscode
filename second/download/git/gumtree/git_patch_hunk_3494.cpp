 	int newmode;
 } _startupinfo;
 
 extern int __wgetmainargs(int *argc, wchar_t ***argv, wchar_t ***env, int glob,
 		_startupinfo *si);
 
-static NORETURN void die_startup()
+static NORETURN void die_startup(void)
 {
 	fputs("fatal: not enough memory for initialization", stderr);
 	exit(128);
 }
 
 static void *malloc_startup(size_t size)
