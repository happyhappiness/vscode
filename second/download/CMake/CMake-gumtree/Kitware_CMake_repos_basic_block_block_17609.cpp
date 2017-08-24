(val == NULL || val[0] == 0) {
			zip->flags &= ~ ZIP_FLAG_EXPERIMENT_xl;
		} else {
			zip->flags |= ZIP_FLAG_EXPERIMENT_xl;
		}