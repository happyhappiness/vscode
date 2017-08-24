(!zip->cctx_valid || zip->aes_vendor != AES_VENDOR_AE_2)
		zip->entry_crc32 =
		    zip->crc32func(zip->entry_crc32, buff, (unsigned)s)