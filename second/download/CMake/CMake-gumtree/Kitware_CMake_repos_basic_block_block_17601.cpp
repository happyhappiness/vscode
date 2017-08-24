{
			zip->flags |= ZIP_FLAG_FORCE_ZIP64;
			zip->flags &= ~ZIP_FLAG_AVOID_ZIP64;
		}