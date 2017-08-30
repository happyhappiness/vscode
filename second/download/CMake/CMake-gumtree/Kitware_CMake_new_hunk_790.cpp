		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,

		    "Unexpected codec ID: %lX", zip->codec);

		return (ARCHIVE_FAILED);

	case _7Z_CRYPTO_MAIN_ZIP:

	case _7Z_CRYPTO_RAR_29:

	case _7Z_CRYPTO_AES_256_SHA_256:

		if (a->entry) {

			archive_entry_set_is_metadata_encrypted(a->entry, 1);

			archive_entry_set_is_data_encrypted(a->entry, 1);

			zip->has_encrypted_entries = 1;

		}

		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,

		    "Crypto codec not supported yet (ID: 0x%lX)", zip->codec);

		return (ARCHIVE_FAILED);

	default:

		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,

		    "Unknown codec ID: %lX", zip->codec);

