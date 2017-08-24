{
			archive_le16enc(e+4, AES_VENDOR_AE_2);
			zip->aes_vendor = AES_VENDOR_AE_2;/* no CRC. */
		}