{
	case 1:	/* 1 byte sequence. */
		*pwc = ch & 0x7f;
		return (cnt);
	case 2:	/* 2 bytes sequence. */
		if ((s[1] & 0xc0) != 0x80) {
			cnt = 1;
			goto invalid_sequence;
		}
		*pwc = ((ch & 0x1f) << 6) | (s[1] & 0x3f);
		return (cnt);
	case 3:	/* 3 bytes sequence. */
		if ((s[1] & 0xc0) != 0x80) {
			cnt = 1;
			goto invalid_sequence;
		}
		if ((s[2] & 0xc0) != 0x80) {
			cnt = 2;
			goto invalid_sequence;
		}
		wc = ((ch & 0x0f) << 12)
		    | ((s[1] & 0x3f) << 6)
		    | (s[2] & 0x3f);
		if (wc < 0x800)
			goto invalid_sequence;/* Overlong sequence. */
		break;
	case 4:	/* 4 bytes sequence. */
		if ((s[1] & 0xc0) != 0x80) {
			cnt = 1;
			goto invalid_sequence;
		}
		if ((s[2] & 0xc0) != 0x80) {
			cnt = 2;
			goto invalid_sequence;
		}
		if ((s[3] & 0xc0) != 0x80) {
			cnt = 3;
			goto invalid_sequence;
		}
		wc = ((ch & 0x07) << 18)
		    | ((s[1] & 0x3f) << 12)
		    | ((s[2] & 0x3f) << 6)
		    | (s[3] & 0x3f);
		if (wc < 0x10000)
			goto invalid_sequence;/* Overlong sequence. */
		break;
	default: /* Others are all invalid sequence. */
		if (ch == 0xc0 || ch == 0xc1)
			cnt = 2;
		else if (ch >= 0xf5 && ch <= 0xf7)
			cnt = 4;
		else if (ch >= 0xf8 && ch <= 0xfb)
			cnt = 5;
		else if (ch == 0xfc || ch == 0xfd)
			cnt = 6;
		else
			cnt = 1;
		if ((int)n < cnt)
			cnt = (int)n;
		for (i = 1; i < cnt; i++) {
			if ((s[i] & 0xc0) != 0x80) {
				cnt = i;
				break;
			}
		}
		goto invalid_sequence;
	}