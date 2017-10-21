		case POPT_ARGFLAG_XOR:
		    *le++ = '^';
		    /*@innerbreak@*/ break;
		default:
		    /*@innerbreak@*/ break;
		}
		*le++ = '=';
		if (negate) *le++ = '~';
		/*@-formatconst@*/
		sprintf(le, (ops ? "0x%lx" : "%ld"), aLong);
		le += strlen(le);
		/*@=formatconst@*/
		*le++ = ']';
	    }	break;
	    case POPT_ARG_INT:
	    case POPT_ARG_LONG:
	    case POPT_ARG_FLOAT:
	    case POPT_ARG_DOUBLE:
	    case POPT_ARG_STRING:
		*le++ = '=';
		strcpy(le, argDescrip);		le += strlen(le);
		break;
	    default:
		break;
	    }
	} else {
	    *le++ = '=';
	    strcpy(le, argDescrip);		le += strlen(le);
	}
	if (opt->argInfo & POPT_ARGFLAG_OPTIONAL)
	    *le++ = ']';
	*le = '\0';
    }

    if (help)
	fprintf(fp,"  %-*s   ", maxLeftCol, left);
    else {
	fprintf(fp,"  %s\n", left); 
	goto out;
    }

    left = _free(left);
    if (defs) {
	help = defs; defs = NULL;
    }

    helpLength = strlen(help);
    while (helpLength > lineLength) {
	const unsigned char * ch;
	char format[10];

	ch = help + lineLength - 1;
	while (ch > help && !isspace(*ch)) ch--;
	if (ch == help) break;		/* give up */
	while (ch > (help + 1) && isspace(*ch)) ch--;
	ch++;

	sprintf(format, "%%.%ds\n%%%ds", (int) (ch - help), indentLength);
	/*@-formatconst@*/
	fprintf(fp, format, help, " ");
	/*@=formatconst@*/
	help = ch;
	while (isspace(*help) && *help) help++;
	helpLength = strlen(help);
    }

    if (helpLength) fprintf(fp, "%s\n", help);

out:
    /*@-dependenttrans@*/
    defs = _free(defs);
    /*@=dependenttrans@*/
    left = _free(left);
}

/**
 * @param opt		option(s)
 * @param translation_domain	translation domain
 */
static int maxArgWidth(const struct poptOption * opt,
		       /*@null@*/ const char * translation_domain)
	/*@*/
{
    int max = 0;
    int len = 0;
    const char * s;
    
    if (opt != NULL)
    while (opt->longName || opt->shortName || opt->arg) {
	if ((opt->argInfo & POPT_ARG_MASK) == POPT_ARG_INCLUDE_TABLE) {
	    if (opt->arg)	/* XXX program error */
