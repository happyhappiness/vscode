static void caterr(char *s)
{
    register char *p = s;

    while (*p >= '0' && *p <= '9')
	p++;
    switch (atoi(s)) {
    case L_ERROR_TOOMANY:
	strcat(errbuf, "to many errors");
	break;
    case L_ERROR_NOLIB:
	strcat(errbuf, "can't load library");
	strcat(errbuf, p);
	break;
    case L_ERROR_UNDEF:
	strcat(errbuf, "can't find symbol");
	strcat(errbuf, p);
	break;
    case L_ERROR_RLDBAD:
	strcat(errbuf, "bad RLD");
	strcat(errbuf, p);
	break;
    case L_ERROR_FORMAT:
	strcat(errbuf, "bad exec format in");
	strcat(errbuf, p);
	break;
    case L_ERROR_ERRNO:
	strcat(errbuf, strerror(atoi(++p)));
	break;
    default:
	strcat(errbuf, s);
	break;
    }
}