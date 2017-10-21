	  read_sbuf(f,line,l);
	  add_exclude(line);
  }
}


static char *cvs_ignore_list[] = {
  "RCS","SCCS","CVS","CVS.adm","RCSLOG","cvslog.*",
  "tags","TAGS",".make.state",".nse_depinfo",
  "*~", "#*", ".#*", ",*", "*.old", "*.bak", "*.BAK", "*.orig",
  "*.rej", ".del-*", "*.a", "*.o", "*.obj", "*.so", "*.Z", "*.elc", "*.ln",
  "core",NULL};
