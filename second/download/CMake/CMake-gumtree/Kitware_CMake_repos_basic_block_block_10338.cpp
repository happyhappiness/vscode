{
		state->signature_len = signature_len;
		state->signature = malloc(signature_len);
		memcpy(state->signature, signature, signature_len);
	}