struct chmod_mode_struct *parse_chmod(const char *modestr,
				      struct chmod_mode_struct **root_mode_ptr)
{
	int state = STATE_1ST_HALF;
	int where = 0, what = 0, op = 0, topbits = 0, topoct = 0, flags = 0;
	struct chmod_mode_struct *first_mode = NULL, *curr_mode = NULL,
				 *prev_mode = NULL;

	while (state != STATE_ERROR) {
		if (!*modestr || *modestr == ',') {
			int bits;

			if (!op) {
				state = STATE_ERROR;
				break;
			}
			prev_mode = curr_mode;
			curr_mode = new_array(struct chmod_mode_struct, 1);
			if (prev_mode)
				prev_mode->next = curr_mode;
			else
				first_mode = curr_mode;
			curr_mode->next = NULL;

			if (where)
				bits = where * what;
			else {
				where = 0111;
				bits = (where * what) & ~orig_umask;
			}

			switch (op) {
			case CHMOD_ADD:
				curr_mode->ModeAND = CHMOD_BITS;
				curr_mode->ModeOR  = bits + topoct;
				break;
			case CHMOD_SUB:
				curr_mode->ModeAND = CHMOD_BITS - bits - topoct;
				curr_mode->ModeOR  = 0;
				break;
			case CHMOD_EQ:
				curr_mode->ModeAND = CHMOD_BITS - (where * 7) - (topoct ? topbits : 0);
				curr_mode->ModeOR  = bits + topoct;
				break;
			case CHMOD_SET:
				curr_mode->ModeAND = 0;
				curr_mode->ModeOR  = bits;
				break;
			}

			curr_mode->flags = flags;

			if (!*modestr)
				break;
			modestr++;

			state = STATE_1ST_HALF;
			where = what = op = topoct = topbits = flags = 0;
		}

		switch (state) {
		case STATE_1ST_HALF:
			switch (*modestr) {
			case 'D':
				if (flags & FLAG_FILES_ONLY)
					state = STATE_ERROR;
				flags |= FLAG_DIRS_ONLY;
				break;
			case 'F':
				if (flags & FLAG_DIRS_ONLY)
					state = STATE_ERROR;
				flags |= FLAG_FILES_ONLY;
				break;
			case 'u':
				where |= 0100;
				topbits |= 04000;
				break;
			case 'g':
				where |= 0010;
				topbits |= 02000;
				break;
			case 'o':
				where |= 0001;
				break;
			case 'a':
				where |= 0111;
				break;
			case '+':
				op = CHMOD_ADD;
				state = STATE_2ND_HALF;
				break;
			case '-':
				op = CHMOD_SUB;
				state = STATE_2ND_HALF;
				break;
			case '=':
				op = CHMOD_EQ;
				state = STATE_2ND_HALF;
				break;
			default:
				if (isDigit(modestr) && *modestr < '8' && !where) {
					op = CHMOD_SET;
					state =  STATE_OCTAL_NUM;
					where = 1;
					what = *modestr - '0';
				} else
					state = STATE_ERROR;
				break;
			}
			break;
		case STATE_2ND_HALF:
			switch (*modestr) {
			case 'r':
				what |= 4;
				break;
			case 'w':
				what |= 2;
				break;
			case 'X':
				flags |= FLAG_X_KEEP;
				/* FALL THROUGH */
			case 'x':
				what |= 1;
				break;
			case 's':
				if (topbits)
					topoct |= topbits;
				else
					topoct = 04000;
				break;
			case 't':
				topoct |= 01000;
				break;
			default:
				state = STATE_ERROR;
				break;
			}
			break;
		case STATE_OCTAL_NUM:
			if (isDigit(modestr) && *modestr < '8') {
				what = what*8 + *modestr - '0';
				if (what > CHMOD_BITS)
					state = STATE_ERROR;
			} else
				state = STATE_ERROR;
			break;
		}
		modestr++;
	}

	if (state == STATE_ERROR) {
		free_chmod_mode(first_mode);
		return NULL;
	}

	if (!(curr_mode = *root_mode_ptr))
		*root_mode_ptr = first_mode;
	else {
		while (curr_mode->next)
			curr_mode = curr_mode->next;
		curr_mode->next = first_mode;
	}

	return first_mode;
}