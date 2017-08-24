{
					f2->nlink = nlink;
					archive_string_copy(
					    &(f2->hardlink), &(file->pathname));
				}