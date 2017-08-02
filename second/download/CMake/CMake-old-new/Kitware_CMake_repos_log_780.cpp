archive_set_error(&a->archive, err,
			    "Internal error initializing decompressor: %s",
			    detail != NULL ? detail : "??")