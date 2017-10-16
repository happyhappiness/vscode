	  strcat(formatbuf, "#");

	fptr=&formatbuf[strlen(formatbuf)];

	if(width >= 0) {
	  /* RECURSIVE USAGE */
          len = curl_msnprintf(fptr, left, "%ld", width);
          fptr += len;
          left -= len;
	}
	if(prec >= 0) {
	  /* RECURSIVE USAGE */
          len = curl_msnprintf(fptr, left, ".%ld", prec);
          fptr += len;
          left -= len;
	}
	if (p->flags & FLAGS_LONG)
          *fptr++ = 'l';

	if (p->flags & FLAGS_FLOATE)
          *fptr++ = p->flags&FLAGS_UPPER ? 'E':'e';
	else if (p->flags & FLAGS_FLOATG)
          *fptr++ = p->flags & FLAGS_UPPER ? 'G' : 'g';
	else
          *fptr++ = 'f';

        *fptr = 0; /* and a final zero termination */

	/* NOTE NOTE NOTE!! Not all sprintf() implementations returns number
	   of output characters */
        (sprintf)(work, formatbuf, p->data.dnum);

	for(fptr=work; *fptr; fptr++)
	  OUTCHAR(*fptr);
      }
      break;

