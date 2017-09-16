{

    /* This could be called from an AddModule httpd.conf command,

     * after the file has been linked and the module structure within it

     * teased out...

     */



    if (m->version != MODULE_MAGIC_NUMBER_MAJOR) {

	fprintf(stderr, "httpd: module \"%s\" is not compatible with this "

		"version of Apache.\n", m->name);

	fprintf(stderr, "Please contact the vendor for the correct version.\n");

	exit(1);

    }



    if (m->next == NULL) {

	m->next = top_module;

	top_module = m;

