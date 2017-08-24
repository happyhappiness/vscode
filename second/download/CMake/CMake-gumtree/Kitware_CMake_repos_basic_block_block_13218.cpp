(attr = list->first; attr != NULL; attr = attr->next) {
		if (strcmp(attr->name, "style") == 0) {
			if (strcmp(attr->value, "application/octet-stream") == 0)
				encoding = NONE;
			else if (strcmp(attr->value, "application/x-gzip") == 0)
				encoding = GZIP;
			else if (strcmp(attr->value, "application/x-bzip2") == 0)
				encoding = BZIP2;
			else if (strcmp(attr->value, "application/x-lzma") == 0)
				encoding = LZMA;
			else if (strcmp(attr->value, "application/x-xz") == 0)
				encoding = XZ;
		}
	}