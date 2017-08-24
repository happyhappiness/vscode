{
		const uint32_t distance = coder->reps[rep];
		rc_bit(&coder->rc, &coder->is_rep0[coder->state], 1);

		if (rep == 1) {
			rc_bit(&coder->rc, &coder->is_rep1[coder->state], 0);
		} else {
			rc_bit(&coder->rc, &coder->is_rep1[coder->state], 1);
			rc_bit(&coder->rc, &coder->is_rep2[coder->state],
					rep - 2);

			if (rep == 3)
				coder->reps[3] = coder->reps[2];

			coder->reps[2] = coder->reps[1];
		}

		coder->reps[1] = coder->reps[0];
		coder->reps[0] = distance;
	}