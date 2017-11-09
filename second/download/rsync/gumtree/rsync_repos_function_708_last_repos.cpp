static int dopr(char *buffer, size_t maxlen, const char *format, va_list args_in)
{
	char ch;
	int state;
	int pflag;
	int pnum;
	int pfirst;
	size_t currlen;
	va_list args;
	const char *base;
	struct pr_chunk *chunks = NULL;
	struct pr_chunk *cnk = NULL;
	struct pr_chunk_x *clist = NULL;
	int max_pos;
	int ret = -1;

	VA_COPY(args, args_in);

	state = DP_S_DEFAULT;
	pfirst = 1;
	pflag = 0;
	pnum = 0;

	max_pos = 0;
	base = format;
	ch = *format++;
	
	/* retrieve the string structure as chunks */
	while (state != DP_S_DONE) {
		if (ch == '\0') 
			state = DP_S_DONE;

		switch(state) {
		case DP_S_DEFAULT:
			
			if (cnk) {
				cnk->next = new_chunk();
				cnk = cnk->next;
			} else {
				cnk = new_chunk();
			}
			if (!cnk) goto done;
			if (!chunks) chunks = cnk;
			
			if (ch == '%') {
				state = DP_S_FLAGS;
				ch = *format++;
			} else {
				cnk->type = CNK_FMT_STR;
				cnk->start = format - base -1;
				while ((ch != '\0') && (ch != '%')) ch = *format++;
				cnk->len = format - base - cnk->start -1;
			}
			break;
		case DP_S_FLAGS:
			switch (ch) {
			case '-':
				cnk->flags |= DP_F_MINUS;
				ch = *format++;
				break;
			case '+':
				cnk->flags |= DP_F_PLUS;
				ch = *format++;
				break;
			case ' ':
				cnk->flags |= DP_F_SPACE;
				ch = *format++;
				break;
			case '#':
				cnk->flags |= DP_F_NUM;
				ch = *format++;
				break;
			case '0':
				cnk->flags |= DP_F_ZERO;
				ch = *format++;
				break;
			case 'I':
				/* internationalization not supported yet */
				ch = *format++;
				break;
			default:
				state = DP_S_MIN;
				break;
			}
			break;
		case DP_S_MIN:
			if (isdigit((unsigned char)ch)) {
				cnk->min = 10 * cnk->min + char_to_int (ch);
				ch = *format++;
			} else if (ch == '$') {
				if (!pfirst && !pflag) {
					/* parameters must be all positioned or none */
					goto done;
				}
				if (pfirst) {
					pfirst = 0;
					pflag = 1;
				}
				if (cnk->min == 0) /* what ?? */
					goto done;
				cnk->num = cnk->min;
				cnk->min = 0;
				ch = *format++;
			} else if (ch == '*') {
				if (pfirst) pfirst = 0;
				cnk->min_star = new_chunk();
				if (!cnk->min_star) /* out of memory :-( */
					goto done;
				cnk->min_star->type = CNK_INT;
				if (pflag) {
					int num;
					ch = *format++;
					if (!isdigit((unsigned char)ch)) {
						/* parameters must be all positioned or none */
						goto done;
					}
					for (num = 0; isdigit((unsigned char)ch); ch = *format++) {
						num = 10 * num + char_to_int(ch);
					}
					cnk->min_star->num = num;
					if (ch != '$') /* what ?? */
						goto done;
				} else {
					cnk->min_star->num = ++pnum;
				}
				max_pos = add_cnk_list_entry(&clist, max_pos, cnk->min_star);
				if (max_pos == 0) /* out of memory :-( */
					goto done;
				ch = *format++;
				state = DP_S_DOT;
			} else {
				if (pfirst) pfirst = 0;
				state = DP_S_DOT;
			}
			break;
		case DP_S_DOT:
			if (ch == '.') {
				state = DP_S_MAX;
				ch = *format++;
			} else { 
				state = DP_S_MOD;
			}
			break;
		case DP_S_MAX:
			if (isdigit((unsigned char)ch)) {
				if (cnk->max < 0)
					cnk->max = 0;
				cnk->max = 10 * cnk->max + char_to_int (ch);
				ch = *format++;
			} else if (ch == '$') {
				if (!pfirst && !pflag) {
					/* parameters must be all positioned or none */
					goto done;
				}
				if (cnk->max <= 0) /* what ?? */
					goto done;
				cnk->num = cnk->max;
				cnk->max = -1;
				ch = *format++;
			} else if (ch == '*') {
				cnk->max_star = new_chunk();
				if (!cnk->max_star) /* out of memory :-( */
					goto done;
				cnk->max_star->type = CNK_INT;
				if (pflag) {
					int num;
					ch = *format++;
					if (!isdigit((unsigned char)ch)) {
						/* parameters must be all positioned or none */
						goto done;
					}
					for (num = 0; isdigit((unsigned char)ch); ch = *format++) {
						num = 10 * num + char_to_int(ch);
					}
					cnk->max_star->num = num;
					if (ch != '$') /* what ?? */
						goto done;
				} else {
					cnk->max_star->num = ++pnum;
				}
				max_pos = add_cnk_list_entry(&clist, max_pos, cnk->max_star);
				if (max_pos == 0) /* out of memory :-( */
					goto done;

				ch = *format++;
				state = DP_S_MOD;
			} else {
				state = DP_S_MOD;
			}
			break;
		case DP_S_MOD:
			switch (ch) {
			case 'h':
				cnk->cflags = DP_C_SHORT;
				ch = *format++;
				if (ch == 'h') {
					cnk->cflags = DP_C_CHAR;
					ch = *format++;
				}
				break;
			case 'l':
				cnk->cflags = DP_C_LONG;
				ch = *format++;
				if (ch == 'l') {	/* It's a long long */
					cnk->cflags = DP_C_LLONG;
					ch = *format++;
				}
				break;
			case 'L':
				cnk->cflags = DP_C_LDOUBLE;
				ch = *format++;
				break;
			case 'z':
				cnk->cflags = DP_C_SIZET;
				ch = *format++;
				break;
			default:
				break;
			}
			state = DP_S_CONV;
			break;
		case DP_S_CONV:
			if (cnk->num == 0) cnk->num = ++pnum;
			max_pos = add_cnk_list_entry(&clist, max_pos, cnk);
			if (max_pos == 0) /* out of memory :-( */
				goto done;
			
			switch (ch) {
			case 'd':
			case 'i':
				cnk->type = CNK_INT;
				break;
			case 'o':
				cnk->type = CNK_OCTAL;
				cnk->flags |= DP_F_UNSIGNED;
				break;
			case 'u':
				cnk->type = CNK_UINT;
				cnk->flags |= DP_F_UNSIGNED;
				break;
			case 'X':
				cnk->flags |= DP_F_UP;
			case 'x':
				cnk->type = CNK_HEX;
				cnk->flags |= DP_F_UNSIGNED;
				break;
			case 'A':
				/* hex float not supported yet */
			case 'E':
			case 'G':
			case 'F':
				cnk->flags |= DP_F_UP;
			case 'a':
				/* hex float not supported yet */
			case 'e':
			case 'f':
			case 'g':
				cnk->type = CNK_FLOAT;
				break;
			case 'c':
				cnk->type = CNK_CHAR;
				break;
			case 's':
				cnk->type = CNK_STRING;
				break;
			case 'p':
				cnk->type = CNK_PTR;
				cnk->flags |= DP_F_UNSIGNED;
				break;
			case 'n':
				cnk->type = CNK_NUM;
				break;
			case '%':
				cnk->type = CNK_PRCNT;
				break;
			default:
				/* Unknown, bail out*/
				goto done;
			}
			ch = *format++;
			state = DP_S_DEFAULT;
			break;
		case DP_S_DONE:
			break;
		default:
			/* hmm? */
			break; /* some picky compilers need this */
		}
	}

	/* retrieve the format arguments */
	for (pnum = 0; pnum < max_pos; pnum++) {
		int i;

		if (clist[pnum].num == 0) {
			/* ignoring a parameter should not be permitted
			 * all parameters must be matched at least once
			 * BUT seem some system ignore this rule ...
			 * at least my glibc based system does --SSS
			 */
#ifdef DEBUG_SNPRINTF
			printf("parameter at position %d not used\n", pnum+1);
#endif
			/* eat the parameter */
			va_arg (args, int);
			continue;
		}
		for (i = 1; i < clist[pnum].num; i++) {
			if (clist[pnum].chunks[0]->type != clist[pnum].chunks[i]->type) {
				/* nooo noo no!
				 * all the references to a parameter
				 * must be of the same type
				 */
				goto done;
			}
		}
		cnk = clist[pnum].chunks[0];
		switch (cnk->type) {
		case CNK_INT:
			if (cnk->cflags == DP_C_SHORT) 
				cnk->value = va_arg (args, int);
			else if (cnk->cflags == DP_C_LONG)
				cnk->value = va_arg (args, long int);
			else if (cnk->cflags == DP_C_LLONG)
				cnk->value = va_arg (args, LLONG);
			else if (cnk->cflags == DP_C_SIZET)
				cnk->value = va_arg (args, ssize_t);
			else
				cnk->value = va_arg (args, int);

			for (i = 1; i < clist[pnum].num; i++) {
				clist[pnum].chunks[i]->value = cnk->value;
			}
			break;

		case CNK_OCTAL:
		case CNK_UINT:
		case CNK_HEX:
			if (cnk->cflags == DP_C_SHORT)
				cnk->value = va_arg (args, unsigned int);
			else if (cnk->cflags == DP_C_LONG)
				cnk->value = (unsigned long int)va_arg (args, unsigned long int);
			else if (cnk->cflags == DP_C_LLONG)
				cnk->value = (LLONG)va_arg (args, unsigned LLONG);
			else if (cnk->cflags == DP_C_SIZET)
				cnk->value = (size_t)va_arg (args, size_t);
			else
				cnk->value = (unsigned int)va_arg (args, unsigned int);

			for (i = 1; i < clist[pnum].num; i++) {
				clist[pnum].chunks[i]->value = cnk->value;
			}
			break;

		case CNK_FLOAT:
			if (cnk->cflags == DP_C_LDOUBLE)
				cnk->fvalue = va_arg (args, LDOUBLE);
			else
				cnk->fvalue = va_arg (args, double);

			for (i = 1; i < clist[pnum].num; i++) {
				clist[pnum].chunks[i]->fvalue = cnk->fvalue;
			}
			break;

		case CNK_CHAR:
			cnk->value = va_arg (args, int);

			for (i = 1; i < clist[pnum].num; i++) {
				clist[pnum].chunks[i]->value = cnk->value;
			}
			break;

		case CNK_STRING:
			cnk->strvalue = va_arg (args, char *);
			if (!cnk->strvalue) cnk->strvalue = "(NULL)";

			for (i = 1; i < clist[pnum].num; i++) {
				clist[pnum].chunks[i]->strvalue = cnk->strvalue;
			}
			break;

		case CNK_PTR:
			cnk->strvalue = va_arg (args, void *);
			for (i = 1; i < clist[pnum].num; i++) {
				clist[pnum].chunks[i]->strvalue = cnk->strvalue;
			}
			break;

		case CNK_NUM:
			if (cnk->cflags == DP_C_CHAR)
				cnk->pnum = va_arg (args, char *);
			else if (cnk->cflags == DP_C_SHORT)
				cnk->pnum = va_arg (args, short int *);
			else if (cnk->cflags == DP_C_LONG)
				cnk->pnum = va_arg (args, long int *);
			else if (cnk->cflags == DP_C_LLONG)
				cnk->pnum = va_arg (args, LLONG *);
			else if (cnk->cflags == DP_C_SIZET)
				cnk->pnum = va_arg (args, ssize_t *);
			else
				cnk->pnum = va_arg (args, int *);

			for (i = 1; i < clist[pnum].num; i++) {
				clist[pnum].chunks[i]->pnum = cnk->pnum;
			}
			break;

		case CNK_PRCNT:
			break;

		default:
			/* what ?? */
			goto done;
		}
	}
	/* print out the actual string from chunks */
	currlen = 0;
	cnk = chunks;
	while (cnk) {
		int len, min, max;

		if (cnk->min_star) min = cnk->min_star->value;
		else min = cnk->min;
		if (cnk->max_star) max = cnk->max_star->value;
		else max = cnk->max;

		switch (cnk->type) {

		case CNK_FMT_STR:
			if (maxlen != 0 && maxlen > currlen) {
				if (maxlen > (currlen + cnk->len)) len = cnk->len;
				else len = maxlen - currlen;

				memcpy(&(buffer[currlen]), &(base[cnk->start]), len);
			}
			currlen += cnk->len;
				
			break;

		case CNK_INT:
		case CNK_UINT:
			fmtint (buffer, &currlen, maxlen, cnk->value, 10, min, max, cnk->flags);
			break;

		case CNK_OCTAL:
			fmtint (buffer, &currlen, maxlen, cnk->value, 8, min, max, cnk->flags);
			break;

		case CNK_HEX:
			fmtint (buffer, &currlen, maxlen, cnk->value, 16, min, max, cnk->flags);
			break;

		case CNK_FLOAT:
			fmtfp (buffer, &currlen, maxlen, cnk->fvalue, min, max, cnk->flags);
			break;

		case CNK_CHAR:
			dopr_outch (buffer, &currlen, maxlen, cnk->value);
			break;

		case CNK_STRING:
			if (max == -1) {
				max = strlen(cnk->strvalue);
			}
			fmtstr (buffer, &currlen, maxlen, cnk->strvalue, cnk->flags, min, max);
			break;

		case CNK_PTR:
			fmtint (buffer, &currlen, maxlen, (long)(cnk->strvalue), 16, min, max, cnk->flags);
			break;

		case CNK_NUM:
			if (cnk->cflags == DP_C_CHAR)
				*((char *)(cnk->pnum)) = (char)currlen;
			else if (cnk->cflags == DP_C_SHORT)
				*((short int *)(cnk->pnum)) = (short int)currlen;
			else if (cnk->cflags == DP_C_LONG)
				*((long int *)(cnk->pnum)) = (long int)currlen;
			else if (cnk->cflags == DP_C_LLONG)
				*((LLONG *)(cnk->pnum)) = (LLONG)currlen;
			else if (cnk->cflags == DP_C_SIZET)
				*((ssize_t *)(cnk->pnum)) = (ssize_t)currlen;
			else
				*((int *)(cnk->pnum)) = (int)currlen;
			break;

		case CNK_PRCNT:
			dopr_outch (buffer, &currlen, maxlen, '%');
			break;

		default:
			/* what ?? */
			goto done;
		}
		cnk = cnk->next;
	}
	if (maxlen != 0) {
		if (currlen < maxlen - 1) 
			buffer[currlen] = '\0';
		else if (maxlen > 0) 
			buffer[maxlen - 1] = '\0';
	}
	ret = currlen;

done:
	va_end(args);

	while (chunks) {
		cnk = chunks->next;
		free(chunks);
		chunks = cnk;
	}
	if (clist) {
		for (pnum = 0; pnum < max_pos; pnum++) {
			if (clist[pnum].chunks) free(clist[pnum].chunks);
		}
		free(clist);
	}
	return ret;
}