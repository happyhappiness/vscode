(i = 0; i < 8; ++i)
		check->buffer.u32[i] = conv32be(check->state.sha256.state[i])