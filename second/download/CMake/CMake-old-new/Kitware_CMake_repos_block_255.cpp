{
	case XML_PARSER_SEVERITY_VALIDITY_WARNING:
	case XML_PARSER_SEVERITY_WARNING:
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "XML Parsing error: %s", msg);
		break;
	case XML_PARSER_SEVERITY_VALIDITY_ERROR:
	case XML_PARSER_SEVERITY_ERROR:
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "XML Parsing error: %s", msg);
		break;
	}