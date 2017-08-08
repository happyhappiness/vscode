{
			XML_ParserFree(parser);
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "XML Parsing failed");
			return (ARCHIVE_FATAL);
		}