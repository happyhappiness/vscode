fprintf(f, " [-%s%s%s%s]", opt->shortName ? "" : "-", item,
	    argDescrip ? (opt->shortName ? " " : "=") : "",
	    argDescrip ? argDescrip : "");