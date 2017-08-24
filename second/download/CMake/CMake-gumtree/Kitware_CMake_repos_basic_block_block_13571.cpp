(zip->decrypted_bytes_remaining == 0)
			zip->decrypted_ptr = zip->decrypted_buffer;
		else
			zip->decrypted_ptr += bytes_avail