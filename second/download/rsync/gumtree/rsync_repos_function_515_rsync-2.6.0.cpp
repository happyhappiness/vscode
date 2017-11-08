static /*@only@*/ /*@null@*/ char *
singleOptionDefaultValue(int lineLength,
		const struct poptOption * opt,
		/*@-paramuse@*/	/* FIX: i18n macros disable with lclint */
		/*@null@*/ const char * translation_domain)
		/*@=paramuse@*/
	/*@*/
{
    const char * defstr = D_(translation_domain, "default");
    char * le = malloc(4*lineLength + 1);
    char * l = le;

    if (le == NULL) return NULL;	/* XXX can't happen */
    *le = '\0';
    *le++ = '(';
    strcpy(le, defstr);	le += strlen(le);
    *le++ = ':';
    *le++ = ' ';
    if (opt->arg)	/* XXX programmer error */
    switch (opt->argInfo & POPT_ARG_MASK) {
    case POPT_ARG_VAL:
    case POPT_ARG_INT:
    {	long aLong = *((int *)opt->arg);
	sprintf(le, "%ld", aLong);
	le += strlen(le);
    }	break;
    case POPT_ARG_LONG:
    {	long aLong = *((long *)opt->arg);
	sprintf(le, "%ld", aLong);
	le += strlen(le);
    }	break;
    case POPT_ARG_FLOAT:
    {	double aDouble = *((float *)opt->arg);
	sprintf(le, "%g", aDouble);
	le += strlen(le);
    }	break;
    case POPT_ARG_DOUBLE:
    {	double aDouble = *((double *)opt->arg);
	sprintf(le, "%g", aDouble);
	le += strlen(le);
    }	break;
    case POPT_ARG_STRING:
    {	const char * s = *(const char **)opt->arg;
	if (s == NULL) {
	    strcpy(le, "null");	le += strlen(le);
	} else {
	    size_t slen = 4*lineLength - (le - l) - sizeof("\"...\")");
	    *le++ = '"';
	    strncpy(le, s, slen); le[slen] = '\0'; le += strlen(le);	
	    if (slen < strlen(s)) {
		strcpy(le, "...");	le += strlen(le);
	    }
	    *le++ = '"';
	}
    }	break;
    case POPT_ARG_NONE:
    default:
	l = _free(l);
	return NULL;
	/*@notreached@*/ break;
    }
    *le++ = ')';
    *le = '\0';

    return l;
}