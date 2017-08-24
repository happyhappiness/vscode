{
		iso9660->wbuff_remaining = (size_t)
		    (sizeof(iso9660->wbuff) - (off - iso9660->wbuff_offset));
	}