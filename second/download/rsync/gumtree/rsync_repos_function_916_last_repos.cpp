int poptSaveLong(long * arg, int argInfo, long aLong)
{
    /* XXX Check alignment, may fail on funky platforms. */
    if (arg == NULL || (((unsigned long)arg) & (sizeof(*arg)-1)))
	return POPT_ERROR_NULLARG;

    if (argInfo & POPT_ARGFLAG_NOT)
	aLong = ~aLong;
    switch (argInfo & POPT_ARGFLAG_LOGICALOPS) {
    case 0:
	*arg = aLong;
	break;
    case POPT_ARGFLAG_OR:
	*arg |= aLong;
	break;
    case POPT_ARGFLAG_AND:
	*arg &= aLong;
	break;
    case POPT_ARGFLAG_XOR:
	*arg ^= aLong;
	break;
    default:
	return POPT_ERROR_BADOPERATION;
	/*@notreached@*/ break;
    }
    return 0;
}