(xar->file->parent != NULL &&
			    ((xar->file->mode & AE_IFMT) == AE_IFDIR))
				xar->file->parent->subdirs++