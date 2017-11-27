
/* TODO
 * Remove all settings but `-f' and `-C'
 */
static void exit_usage (int status)
{
	printf ("Usage: "PACKAGE_NAME" [OPTIONS]\n\n"

			"Available options:\n"
			"  General:\n"
			"    -C <file>       Configuration file.\n"
			"                    Default: "CONFIGFILE"\n"
			"    -t              Test config and exit.\n"
