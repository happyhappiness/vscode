(; length >= LBYTES; length -= LBYTES, p += LBYTES)
		uu_encode(&state->encoded_buff, p, LBYTES)