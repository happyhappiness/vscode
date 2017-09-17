{
    /* This could be called from an AddModule httpd.conf command,
     * after the file has been linked and the module structure within it
     * teased out...
     */

    /* At some point, we may want to offer back-compatibility for
     * loading modules that are for older versions of Apache. For now,
     * though, we don't.
     */

    if (m->version != MODULE_MAGIC_NUMBER) {
	fprintf(stderr, "httpd: module \"%s\" is not compatible with this "
		"version of Apache.\n", m->name);
	fprintf(stderr, "Please contact the author for the correct version.\n");
	exit(1);
    }

    if (m->next == NULL) {
	m->next = top_module;
	top_module = m;
