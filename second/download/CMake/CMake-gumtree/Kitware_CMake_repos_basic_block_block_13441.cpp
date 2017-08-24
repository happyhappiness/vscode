{
		uint8_t t = in[i] ^ trad_enc_decrypt_byte(ctx);
		out[i] = t;
		trad_enc_update_keys(ctx, t);
	}