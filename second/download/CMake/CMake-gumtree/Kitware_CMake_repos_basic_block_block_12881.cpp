(strcmp(key, "GNU.sparse.minor") == 0) {
			tar->sparse_gnu_minor = (int)tar_atol10(value, strlen(value));
			tar->sparse_gnu_pending = 1;
		}