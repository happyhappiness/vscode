{
			archive_le32enc(e,  /* external file attributes */
			    ((uint32_t)archive_entry_mode(zip->entry)) << 16);
			e += 4;
		}