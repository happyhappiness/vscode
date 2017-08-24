(fullpath != NULL) {
				fd = _wopen(fullpath, O_RDONLY | O_BINARY);
				free(fullpath);
			}