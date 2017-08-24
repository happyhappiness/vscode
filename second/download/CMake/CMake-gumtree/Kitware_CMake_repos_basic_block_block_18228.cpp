{
		// Literal i.e. eight-bit byte
		assert(len == 1);
		rc_bit(&coder->rc,
				&coder->is_match[coder->state][pos_state], 0);
		literal(coder, mf, position);
	}