static BOOL do_section(char *sectionname)
{
	BOOL isglobal;

	if (*sectionname == ']') { /* A special push/pop/reset directive from params.c */
		bInGlobalSection = 1;
		if (strcmp(sectionname+1, "push") == 0) {
			all_vars *vp = EXPAND_ITEM_LIST(&Vars_stack, all_vars, 2);
			memcpy(vp, &Vars, sizeof Vars);
		} else if (strcmp(sectionname+1, "pop") == 0
		 || strcmp(sectionname+1, "reset") == 0) {
			all_vars *vp = ((all_vars*)Vars_stack.items) + Vars_stack.count - 1;
			if (!Vars_stack.count)
				return False;
			memcpy(&Vars, vp, sizeof Vars);
			if (sectionname[1] == 'p')
				Vars_stack.count--;
		} else
			return False;
		return True;
	}

	isglobal = strwicmp(sectionname, GLOBAL_NAME) == 0;

	/* At the end of the global section, add any --dparam items. */
	if (bInGlobalSection && !isglobal) {
		if (!section_list.count)
			set_dparams(0);
	}

	/* if we've just struck a global section, note the fact. */
	bInGlobalSection = isglobal;

	/* check for multiple global sections */
	if (bInGlobalSection)
		return True;

#if 0
	/* If we have a current section, tidy it up before moving on. */
	if (iSectionIndex >= 0) {
		/* Add any tidy work as needed ... */
		if (problem)
			return False;
	}
#endif

	if (strchr(sectionname, '/') != NULL) {
		rprintf(FLOG, "Warning: invalid section name in configuration file: %s\n", sectionname);
		return False;
	}

	if ((iSectionIndex = add_a_section(sectionname)) < 0) {
		rprintf(FLOG, "Failed to add a new module\n");
		bInGlobalSection = True;
		return False;
	}

	return True;
}