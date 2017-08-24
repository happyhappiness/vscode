(;u32num > 0; --u32num) {
		sum ^= archive_le32dec(b);
		b += 4;
	}