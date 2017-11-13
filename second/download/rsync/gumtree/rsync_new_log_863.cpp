fprintf(fp, " [-%c|-%s%s%s%s]",
	    opt->shortName, ((opt->argInfo & POPT_ARGFLAG_ONEDASH) ? "" : "-"),
	    opt->longName,
	    (argDescrip ? " " : ""),
	    (argDescrip ? argDescrip : ""));