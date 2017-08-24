((r = xmlTextReaderRead(reader)) == 1) {
		const char *name, *value;
		int type, empty;

		type = xmlTextReaderNodeType(reader);
		name = (const char *)xmlTextReaderConstLocalName(reader);
		switch (type) {
		case XML_READER_TYPE_ELEMENT:
			empty = xmlTextReaderIsEmptyElement(reader);
			r = xml2_xmlattr_setup(a, &list, reader);
			if (r == ARCHIVE_OK)
				r = xml_start(a, name, &list);
			xmlattr_cleanup(&list);
			if (r != ARCHIVE_OK)
				return (r);
			if (empty)
				xml_end(a, name);
			break;
		case XML_READER_TYPE_END_ELEMENT:
			xml_end(a, name);
			break;
		case XML_READER_TYPE_TEXT:
			value = (const char *)xmlTextReaderConstValue(reader);
			xml_data(a, value, strlen(value));
			break;
		case XML_READER_TYPE_SIGNIFICANT_WHITESPACE:
		default:
			break;
		}
		if (r < 0)
			break;
	}