		case POPT_ARGFLAG_XOR:
		    *le++ = '^';
		    /*@innerbreak@*/ break;
		default:
		    /*@innerbreak@*/ break;
		}
		*le++ = (opt->longName != NULL ? '=' : ' ');
		if (negate) *le++ = '~';
		/*@-formatconst@*/
		limit = nb - (le - left);
		lelen = snprintf(le, limit, (ops ? "0x%lx" : "%ld"), aLong);
		le += lelen >= limit ? limit - 1 : lelen;
		/*@=formatconst@*/
		*le++ = ']';
	    }
#endif
		break;
	    case POPT_ARG_INT:
	    case POPT_ARG_LONG:
	    case POPT_ARG_FLOAT:
	    case POPT_ARG_DOUBLE:
	    case POPT_ARG_STRING:
		*le++ = (opt->longName != NULL ? '=' : ' ');
		limit = nb - (le - left);
		lelen = strlcpy(le, argDescrip, limit);
		le += lelen >= limit ? limit - 1 : lelen;
		break;
	    default:
		break;
	    }
	} else {

	    *le++ = '=';
	    limit = nb - (le - left);
	    lelen = strlcpy(le, argDescrip, limit);
	    if (lelen >= limit)
		lelen = limit - 1;
	    le += lelen;

#ifdef	POPT_WCHAR_HACK
	    {	const char * scopy = argDescrip;
		mbstate_t t;
		size_t n;

		memset ((void *)&t, '\0', sizeof (t));	/* In initial state.  */
		/* Determine number of characters.  */
		n = mbsrtowcs (NULL, &scopy, strlen(scopy), &t);

		displaypad = (int) (lelen-n);
	    }
#endif
	}
	if (opt->argInfo & POPT_ARGFLAG_OPTIONAL)
	    *le++ = ']';
	*le = '\0';
    }
/*@=boundswrite@*/

    if (help)
	fprintf(fp,"  %-*s   ", (int)maxLeftCol+displaypad, left);
    else {
	fprintf(fp,"  %s\n", left); 
	goto out;
    }

    left = _free(left);
/*@-branchstate@*/
    if (defs) {
	help = defs;
	defs = NULL;
    }
/*@=branchstate@*/

    helpLength = strlen(help);
/*@-boundsread@*/
    while (helpLength > lineLength) {
	const char * ch;
	char format[16];

	ch = help + lineLength - 1;
	while (ch > help && !isSpace(ch)) ch--;
	if (ch == help) break;		/* give up */
	while (ch > (help + 1) && isSpace(ch)) ch--;
	ch++;

	snprintf(format, sizeof format, "%%.%ds\n%%%ds", (int) (ch - help), (int) indentLength);
	/*@-formatconst@*/
	fprintf(fp, format, help, " ");
	/*@=formatconst@*/
	help = ch;
	while (isSpace(help) && *help) help++;
	helpLength = strlen(help);
    }
/*@=boundsread@*/

    if (helpLength) fprintf(fp, "%s\n", help);

out:
    /*@-dependenttrans@*/
    defs = _free(defs);
    /*@=dependenttrans@*/
    left = _free(left);
}

/**
 * Find display width for longest argument string.
 * @param opt		option(s)
 * @param translation_domain	translation domain
 * @return		display width
 */
static size_t maxArgWidth(const struct poptOption * opt,
		       /*@null@*/ UNUSED(const char * translation_domain))
	/*@*/
{
    size_t max = 0;
    size_t len = 0;
    const char * s;
    
    if (opt != NULL)
    while (opt->longName || opt->shortName || opt->arg) {
	if ((opt->argInfo & POPT_ARG_MASK) == POPT_ARG_INCLUDE_TABLE) {
	    if (opt->arg)	/* XXX program error */
