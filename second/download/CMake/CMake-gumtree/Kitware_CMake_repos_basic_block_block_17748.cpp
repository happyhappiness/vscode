(type == AE_IFDIR &&
	    (path[0] == '\0' || path[strlen(path) - 1] != '/')) {
		return strlen(path) + 1;
	} else {
		return strlen(path);
	}