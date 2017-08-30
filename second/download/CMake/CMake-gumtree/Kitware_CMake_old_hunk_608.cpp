	 * and are not terminated in '/', so we don't trim anything

	 * that starts with '/'.)

	 */

	if (filename[0] != '/' && *p == '/')

		*p = '\0';



	/*

	 * '//' is the GNU filename table.

