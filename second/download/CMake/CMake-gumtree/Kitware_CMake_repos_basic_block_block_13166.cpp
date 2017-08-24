{
			file->hdnext = hdlink->files;
			hdlink->cnt++;
			hdlink->files = file;
			return (ARCHIVE_OK);
		}