(zip->entry_flags & ZIP_ENTRY_FLAG_LENGTH_AT_END)
			zip->trad_chkdat = local_header[11];
		else
			zip->trad_chkdat = local_header[17]