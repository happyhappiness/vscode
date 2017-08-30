	if (AE_IFREG != (zip->entry->mode & AE_IFMT))

		return (ARCHIVE_EOF);



	__archive_read_consume(a, zip->unconsumed);

	zip->unconsumed = 0;



	if (zip->init_decryption) {

		zip->has_encrypted_entries = 1;

		if (zip->entry->zip_flags & ZIP_STRONG_ENCRYPTED)

			r = read_decryption_header(a);

		else if (zip->entry->compression == WINZIP_AES_ENCRYPTION)

			r = init_WinZip_AES_decryption(a);

		else

			r = init_traditional_PKWARE_decryption(a);

		if (r != ARCHIVE_OK)

			return (r);

		zip->init_decryption = 0;

	}



	switch(zip->entry->compression) {

	case 0:  /* No compression. */

		r =  zip_read_data_none(a, buff, size, offset);

