static int showShortOptions(const struct poptOption * opt, FILE * f, 
			    char * str) {
    char s[300];		/* this is larger then the ascii set, so
				   it should do just fine */

    s[0] = '\0';
    if (str == NULL) {
	memset(s, 0, sizeof(s));
	str = s;
    }

    while (opt->longName || opt->shortName || opt->arg) {
	if (opt->shortName && !(opt->argInfo & POPT_ARG_MASK))
	    str[strlen(str)] = opt->shortName;
	else if ((opt->argInfo & POPT_ARG_MASK) == POPT_ARG_INCLUDE_TABLE)
	    showShortOptions(opt->arg, f, str);

	opt++;
    } 

    if (s != str || !*s)
	return 0;

    fprintf(f, " [-%s]", s);
    return strlen(s) + 4;
}