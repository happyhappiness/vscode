{
			zip->tmp_stream_buff_size = 32 * 1024;
			zip->tmp_stream_buff =
			    malloc(zip->tmp_stream_buff_size);
			if (zip->tmp_stream_buff == NULL) {
				archive_set_error(&a->archive, ENOMEM,
				    "No memory for 7-Zip decompression");
				return (ARCHIVE_FATAL);
			}
		}