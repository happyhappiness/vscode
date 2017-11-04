fprintf(fp, " [-%s%s%s%s]",
	((opt->shortName || (opt->argInfo & POPT_ARGFLAG_ONEDASH)) ? "" : "-"),
	item,
	(argDescrip ? (opt->shortName != '\0' ? " " : "=") : ""),
	(argDescrip ? argDescrip : ""));