ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
			      "XML request body is larger than the configured "
			      "limit of %lu", (unsigned long)limit_xml_body);