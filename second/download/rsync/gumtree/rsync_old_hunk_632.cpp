		    return POPT_ERROR_BADOPT;
	    }

	    if (!opt) {
		con->os->nextCharArg = origOptString + 1;
	    } else {
		if(con->os == con->optionStack &&
		   opt->argInfo & POPT_ARGFLAG_STRIP) {
		    canstrip = 1;
		    poptStripArg(con, thisopt);
		}
	    }
	}

	/* Process next short option */
	if (con->os->nextCharArg) {
	    origOptString = con->os->nextCharArg;

	    con->os->nextCharArg = NULL;

	    if (handleAlias(con, NULL, *origOptString,
			    origOptString + 1)) {
		origOptString++;
		continue;
	    }
	    if (handleExec(con, NULL, *origOptString))
		continue;

	    opt = findOption(con->options, NULL, *origOptString, &cb,
			     &cbData, 0);
	    if (!opt)
		return POPT_ERROR_BADOPT;

	    origOptString++;
	    if (*origOptString)
		con->os->nextCharArg = origOptString;
	}

	if (opt->arg && (opt->argInfo & POPT_ARG_MASK) == POPT_ARG_NONE) {
	    *((int *)opt->arg) = 1;
	} else if ((opt->argInfo & POPT_ARG_MASK) == POPT_ARG_VAL) {
	    if (opt->arg)
		*((int *) opt->arg) = opt->val;
	} else if ((opt->argInfo & POPT_ARG_MASK) != POPT_ARG_NONE) {
	    if (con->os->nextArg) {
		xfree(con->os->nextArg);
		con->os->nextArg = NULL;
	    }
	    if (longArg) {
		con->os->nextArg = expandNextArg(con, longArg);
	    } else if (con->os->nextCharArg) {
		con->os->nextArg = expandNextArg(con, con->os->nextCharArg);
		con->os->nextCharArg = NULL;
	    } else {
		while (con->os->next == con->os->argc &&
		       con->os > con->optionStack) {
		    cleanOSE(con->os--);
		}
		if (con->os->next == con->os->argc)
		    return POPT_ERROR_NOARG;

		/* make sure this isn't part of a short arg or the
                   result of an alias expansion */
		if(con->os == con->optionStack &&
		   opt->argInfo & POPT_ARGFLAG_STRIP &&
		   canstrip) {
		    poptStripArg(con, con->os->next);
		}
		
		con->os->nextArg = expandNextArg(con, con->os->argv[con->os->next++]);
	    }

	    if (opt->arg) {
		long aLong;
		char *end;

		switch (opt->argInfo & POPT_ARG_MASK) {
		  case POPT_ARG_STRING:
		    /* XXX memory leak, hard to plug */
		    *((const char **) opt->arg) = xstrdup(con->os->nextArg);
		    break;

		  case POPT_ARG_INT:
		  case POPT_ARG_LONG:
		    aLong = strtol(con->os->nextArg, &end, 0);
		    if (!(end && *end == '\0'))
			return POPT_ERROR_BADNUMBER;

		    if (aLong == LONG_MIN || aLong == LONG_MAX)
			return POPT_ERROR_OVERFLOW;
		    if ((opt->argInfo & POPT_ARG_MASK) == POPT_ARG_LONG) {
			*((long *) opt->arg) = aLong;
		    } else {
			if (aLong > INT_MAX || aLong < INT_MIN)
			    return POPT_ERROR_OVERFLOW;
			*((int *) opt->arg) = aLong;
		    }
		    break;

		  default:
		    fprintf(stdout, POPT_("option type (%d) not implemented in popt\n"),
		      opt->argInfo & POPT_ARG_MASK);
		    exit(EXIT_FAILURE);
		}
	    }
	}

	if (cb)
	    cb(con, POPT_CALLBACK_REASON_OPTION, opt, con->os->nextArg, cbData);
	else if (opt->val && ((opt->argInfo & POPT_ARG_MASK) != POPT_ARG_VAL))
	    done = 1;

	if ((con->finalArgvCount + 2) >= (con->finalArgvAlloced)) {
	    con->finalArgvAlloced += 10;
	    con->finalArgv = realloc(con->finalArgv,
			    sizeof(*con->finalArgv) * con->finalArgvAlloced);
	}

	{    char *s = malloc((opt->longName ? strlen(opt->longName) : 0) + 3);
	    if (opt->longName)
		sprintf(s, "--%s", opt->longName);
	    else
		sprintf(s, "-%c", opt->shortName);
	    con->finalArgv[con->finalArgvCount++] = s;
	}

	if (opt->arg && (opt->argInfo & POPT_ARG_MASK) != POPT_ARG_NONE
		     && (opt->argInfo & POPT_ARG_MASK) != POPT_ARG_VAL) {
	    con->finalArgv[con->finalArgvCount++] = xstrdup(con->os->nextArg);
	}
    }

    return opt->val;
}

const char * poptGetOptArg(poptContext con) {
    const char * ret = con->os->nextArg;
    con->os->nextArg = NULL;
    return ret;
}

const char * poptGetArg(poptContext con) {
    if (con->numLeftovers == con->nextLeftover) return NULL;
    return con->leftovers[con->nextLeftover++];
}

const char * poptPeekArg(poptContext con) {
    if (con->numLeftovers == con->nextLeftover) return NULL;
    return con->leftovers[con->nextLeftover];
}

const char ** poptGetArgs(poptContext con) {
    if (con->numLeftovers == con->nextLeftover) return NULL;

    /* some apps like [like RPM ;-) ] need this NULL terminated */
    con->leftovers[con->numLeftovers] = NULL;

    return (con->leftovers + con->nextLeftover);
}

void poptFreeContext(poptContext con) {
    int i;

    poptResetContext(con);
    if (con->os->argb) free(con->os->argb);

    for (i = 0; i < con->numAliases; i++) {
	if (con->aliases[i].longName) xfree(con->aliases[i].longName);
	free(con->aliases[i].argv);
    }

    for (i = 0; i < con->numExecs; i++) {
	if (con->execs[i].longName) xfree(con->execs[i].longName);
	xfree(con->execs[i].script);
    }
    if (con->execs) xfree(con->execs);

    free(con->leftovers);
    free(con->finalArgv);
    if (con->appName) xfree(con->appName);
    if (con->aliases) free(con->aliases);
    if (con->otherHelp) xfree(con->otherHelp);
    if (con->execPath) xfree(con->execPath);
    if (con->arg_strip) PBM_FREE(con->arg_strip);
    
    free(con);
}

int poptAddAlias(poptContext con, struct poptAlias newAlias,
		/*@unused@*/ int flags)
{
    int aliasNum = con->numAliases++;
    struct poptAlias * alias;

    /* SunOS won't realloc(NULL, ...) */
    if (!con->aliases)
	con->aliases = malloc(sizeof(newAlias) * con->numAliases);
    else
	con->aliases = realloc(con->aliases,
			       sizeof(newAlias) * con->numAliases);
    alias = con->aliases + aliasNum;

    alias->longName = (newAlias.longName)
	? strcpy(malloc(strlen(newAlias.longName) + 1), newAlias.longName)
	: NULL;
    alias->shortName = newAlias.shortName;
    alias->argc = newAlias.argc;
    alias->argv = newAlias.argv;

    return 0;
}

const char * poptBadOption(poptContext con, int flags) {
    struct optionStackEntry * os;

    if (flags & POPT_BADOPTION_NOALIAS)
	os = con->optionStack;
    else
	os = con->os;

    return os->argv[os->next - 1];
}

#define POPT_ERROR_NOARG	-10
#define POPT_ERROR_BADOPT	-11
#define POPT_ERROR_OPTSTOODEEP	-13
#define POPT_ERROR_BADQUOTE	-15	/* only from poptParseArgString() */
#define POPT_ERROR_ERRNO	-16	/* only from poptParseArgString() */

const char *const poptStrerror(const int error) {
    switch (error) {
      case POPT_ERROR_NOARG:
	return POPT_("missing argument");
      case POPT_ERROR_BADOPT:
	return POPT_("unknown option");
      case POPT_ERROR_OPTSTOODEEP:
	return POPT_("aliases nested too deeply");
      case POPT_ERROR_BADQUOTE:
	return POPT_("error in paramter quoting");
      case POPT_ERROR_BADNUMBER:
	return POPT_("invalid numeric value");
      case POPT_ERROR_OVERFLOW:
	return POPT_("number too large or too small");
      case POPT_ERROR_ERRNO:
	return strerror(errno);
      default:
	return POPT_("unknown error");
    }
}

int poptStuffArgs(poptContext con, const char ** argv) {
    int argc;

    if ((con->os - con->optionStack) == POPT_OPTION_DEPTH)
	return POPT_ERROR_OPTSTOODEEP;

    for (argc = 0; argv[argc]; argc++)
	;

    con->os++;
    con->os->next = 0;
    con->os->nextArg = NULL;
    con->os->nextCharArg = NULL;
    con->os->currAlias = NULL;
    poptDupArgv(argc, argv, &con->os->argc, &con->os->argv);
    con->os->argb = NULL;
    con->os->stuffed = 1;

    return 0;
}

const char * poptGetInvocationName(poptContext con) {
    return con->os->argv[0];
}

int poptStrippedArgv(poptContext con, int argc, char **argv)
{
    int i,j=1, numargs=argc;
    
    for(i=1; i<argc; i++) {
	if(PBM_ISSET(i, con->arg_strip)) {
	    numargs--;
	}
    }
    
    for(i=1; i<argc; i++) {
	if(PBM_ISSET(i, con->arg_strip)) {
	    continue;
	} else {
	    if(j<numargs) {
		argv[j++]=argv[i];
	    } else {
		argv[j++]='\0';
	    }
	}
    }
    
    return(numargs);
}
