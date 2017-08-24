(state->first_free < state->max_maxcode) {
			state->codetab[i] = state->first_free++;	/* code -> hashtable */
			state->hashtab[i] = state->cur_fcode;
			continue;
		}