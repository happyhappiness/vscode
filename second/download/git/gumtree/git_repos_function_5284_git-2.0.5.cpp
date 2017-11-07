char *mingw_getenv(const char *name)
{
	char *result = getenv_cs(name);
	if (!result && !strcmp(name, "TMPDIR")) {
		/* on Windows it is TMP and TEMP */
		result = getenv_cs("TMP");
		if (!result)
			result = getenv_cs("TEMP");
	}
	return result;
}