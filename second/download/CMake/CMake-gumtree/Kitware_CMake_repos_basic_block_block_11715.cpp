(file->size > 0 &&
			    (file->mode & AE_IFMT) == AE_IFLNK) {
				file->size = 0;
				file->number = -1;
				file->offset = -1;
			}