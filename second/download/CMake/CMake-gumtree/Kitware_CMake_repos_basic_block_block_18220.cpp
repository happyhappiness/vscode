{
		rc_bit(rc, &lc->choice, 1);
		len -= LEN_LOW_SYMBOLS;

		if (len < LEN_MID_SYMBOLS) {
			rc_bit(rc, &lc->choice2, 0);
			rc_bittree(rc, lc->mid[pos_state], LEN_MID_BITS, len);
		} else {
			rc_bit(rc, &lc->choice2, 1);
			len -= LEN_MID_SYMBOLS;
			rc_bittree(rc, lc->high, LEN_HIGH_BITS, len);
		}
	}