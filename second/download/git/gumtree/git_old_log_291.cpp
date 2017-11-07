packet_write(1, "%s %s%c%s\n",
			     sha1_to_hex(sha1), path, 0, cap.buf);