{
		keccak_theta(state);

		/* apply Keccak rho() transformation */
		state[ 1] = ROTL64(state[ 1],  1);
		state[ 2] = ROTL64(state[ 2], 62);
		state[ 3] = ROTL64(state[ 3], 28);
		state[ 4] = ROTL64(state[ 4], 27);
		state[ 5] = ROTL64(state[ 5], 36);
		state[ 6] = ROTL64(state[ 6], 44);
		state[ 7] = ROTL64(state[ 7],  6);
		state[ 8] = ROTL64(state[ 8], 55);
		state[ 9] = ROTL64(state[ 9], 20);
		state[10] = ROTL64(state[10],  3);
		state[11] = ROTL64(state[11], 10);
		state[12] = ROTL64(state[12], 43);
		state[13] = ROTL64(state[13], 25);
		state[14] = ROTL64(state[14], 39);
		state[15] = ROTL64(state[15], 41);
		state[16] = ROTL64(state[16], 45);
		state[17] = ROTL64(state[17], 15);
		state[18] = ROTL64(state[18], 21);
		state[19] = ROTL64(state[19],  8);
		state[20] = ROTL64(state[20], 18);
		state[21] = ROTL64(state[21],  2);
		state[22] = ROTL64(state[22], 61);
		state[23] = ROTL64(state[23], 56);
		state[24] = ROTL64(state[24], 14);

		keccak_pi(state);
		keccak_chi(state);

		/* apply iota(state, round) */
		*state ^= keccak_round_constants[round];
	}