(i = 0; i < max; i++) {
		uint8_t t = in[i];
		out[i] = t ^ trad_enc_decrypt_byte(ctx);
		trad_enc_update_keys(ctx, t);
	}