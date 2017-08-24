{
		size_t l = x86_Convert(zip, buff, *outbytes);
		zip->odd_bcj_size = *outbytes - l;
		if (zip->odd_bcj_size > 0 && zip->odd_bcj_size <= 4 &&
		    o_avail_in && ret != ARCHIVE_EOF) {
			memcpy(zip->odd_bcj, ((unsigned char *)buff) + l,
			    zip->odd_bcj_size);
			*outbytes = l;
		} else
			zip->odd_bcj_size = 0;
	}