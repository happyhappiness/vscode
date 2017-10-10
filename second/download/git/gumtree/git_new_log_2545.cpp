fprintf(stderr,
				"Resuming fetch of pack %s at byte %"PRIuMAX"\n",
				sha1_to_hex(target->sha1), (uintmax_t)prev_posn);