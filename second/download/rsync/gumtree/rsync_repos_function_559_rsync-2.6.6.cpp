static int poptSaveLong(const struct poptOption * opt, long aLong)
	/*@modifies opt->arg @*/
{
    if (opt->arg == NULL)
	return POPT_ERROR_NULLARG;

    if (opt->argInfo & POPT_ARGFLAG_NOT)
	aLong = ~aLong;
    switch (opt->argInfo & POPT_ARGFLAG_LOGICALOPS) {
    case 0:
	*((long *) opt->arg) = aLong;
	break;
    case POPT_ARGFLAG_OR:
	*((long *) opt->arg) |= aLong;
	break;
    case POPT_ARGFLAG_AND:
	*((long *) opt->arg) &= aLong;
	break;
    case POPT_ARGFLAG_XOR:
	*((long *) opt->arg) ^= aLong;
	break;
    default:
	return POPT_ERROR_BADOPERATION;
	/*@notreached@*/ break;
    }
    return 0;
}