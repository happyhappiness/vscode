archive_set_error(&self->archive->archive, err,
				    "Internal error initializing decompressor%s%s",
				    detail == NULL ? "" : ": ",
				    detail)