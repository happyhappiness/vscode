(fidx=0; folder && fidx<folder->numCoders; fidx++) {
			switch(folder->coders[fidx].codec) {
				case _7Z_CRYPTO_MAIN_ZIP:
				case _7Z_CRYPTO_RAR_29:
				case _7Z_CRYPTO_AES_256_SHA_256: {
					archive_entry_set_is_data_encrypted(entry, 1);
					zip->has_encrypted_entries = 1;
					break;
				}
			}
		}