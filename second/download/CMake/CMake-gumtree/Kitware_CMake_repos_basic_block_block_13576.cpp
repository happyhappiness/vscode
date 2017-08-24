(zip->entry_bytes_remaining <
					      (int64_t)zip->decrypted_bytes_remaining)
						buff_remaining = 0;
					else
						buff_remaining =
						    (size_t)zip->entry_bytes_remaining
						      - zip->decrypted_bytes_remaining