((s[2] & 0xc0) != 0x80) {
			cnt = 2;
			goto invalid_sequence;
		}