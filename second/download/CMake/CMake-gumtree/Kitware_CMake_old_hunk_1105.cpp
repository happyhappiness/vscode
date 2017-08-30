	if (strcmp(key, "compat-2x")  == 0) {

		/* Handle filnames as libarchive 2.x */

		zip->init_default_conversion = (val != NULL) ? 1 : 0;

		ret = ARCHIVE_OK;

	} else if (strcmp(key, "hdrcharset")  == 0) {

		if (val == NULL || val[0] == 0)

			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,

			    "zip: hdrcharset option needs a character-set name");

		else {

			zip->sconv = archive_string_conversion_from_charset(

			    &a->archive, val, 0);

