{
			/*
			 * The real filename; when storing sparse
			 * files, GNU tar puts a synthesized name into
			 * the regular 'path' attribute in an attempt
			 * to limit confusion. ;-)
			 */
			archive_strcpy(&(tar->entry_pathname_override), value);
		}