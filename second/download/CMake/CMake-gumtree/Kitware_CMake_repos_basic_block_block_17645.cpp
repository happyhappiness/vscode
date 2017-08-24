{

		memcpy(e, "\001\231\007\000\001\000AE", 8);
		/* AES vendor version AE-2 does not store a CRC.
		 * WinZip 11 uses AE-1, which does store the CRC,
		 * but it does not store the CRC when the file size
		 * is less than 20 bytes. So we simulate what
		 * WinZip 11 does.
		 * NOTE: WinZip 9.0 and 10.0 uses AE-2 by default. */
		if (archive_entry_size_is_set(zip->entry)
		    && archive_entry_size(zip->entry) < 20) {
			archive_le16enc(e+4, AES_VENDOR_AE_2);
			zip->aes_vendor = AES_VENDOR_AE_2;/* no CRC. */
		} else
			zip->aes_vendor = AES_VENDOR_AE_1;
		e += 8;
		/* AES encryption strength. */
		*e++ = (zip->entry_encryption == ENCRYPTION_WINZIP_AES128)?1:3;
		/* Actual compression method. */
		archive_le16enc(e, zip->entry_compression);
		e += 2;
	}