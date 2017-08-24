h(folder->coders[i].codec) {
			case _7Z_CRYPTO_MAIN_ZIP:
			case _7Z_CRYPTO_RAR_29:
			case _7Z_CRYPTO_AES_256_SHA_256: {
				/* For entry that is associated with this folder, mark
				   it as encrypted (data+metadata). */
				zip->has_encrypted_entries = 1;
				if (a->entry) {
					archive_entry_set_is_data_encrypted(a->entry, 1);
					archive_entry_set_is_metadata_encrypted(a->entry, 1);
				}
				archive_set_error(&(a->archive),
					ARCHIVE_ERRNO_MISC,
					"The %s is encrypted, "
					"but currently not supported", cname);
				return (ARCHIVE_FATAL);
			}
			case _7Z_X86_BCJ2: {
				found_bcj2++;
				break;
			}
		}