{
			/* Do not compress "._XXX" files. */
			a->todo &= ~TODO_HFS_COMPRESSION;
			if (a->filesize > 0)
				a->todo |= TODO_APPLEDOUBLE;
		}