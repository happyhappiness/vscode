

	if (value == NULL)

		return (ARCHIVE_OK);

	

	r = xmlTextWriterStartElement(writer, BAD_CAST_CONST(key));

	if (r < 0) {

		archive_set_error(&a->archive,

