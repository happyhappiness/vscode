   case 'h': filenames = FALSE; break;
   case 'i': options |= PCRE_CASELESS; break;
   case 'l': filenames_only = TRUE;
   case 'n': number = TRUE; break;
   case 'r': recurse = TRUE; break;
   case 's': silent = TRUE; break;
+  case 'u': options |= PCRE_UTF8; break;
   case 'v': invert = TRUE; break;
   case 'x': whole_lines = TRUE; options |= PCRE_ANCHORED; break;
 
   case 'V':
   fprintf(stderr, "pcregrep version %s using ", VERSION);
   fprintf(stderr, "PCRE version %s\n", pcre_version());
