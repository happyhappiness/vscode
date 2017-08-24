{
			zip_entry->mode &= ~AE_IFMT;
			zip_entry->mode |= AE_IFDIR;
			zip_entry->mode |= 0111;
		}