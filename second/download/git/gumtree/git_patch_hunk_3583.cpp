 		} else {
 			patch->old_name = name;
 			patch->new_name = xstrdup_or_null(name);
 		}
 	}
 	if (!name)
-		die(_("unable to find filename in patch at line %d"), linenr);
+		die(_("unable to find filename in patch at line %d"), state->linenr);
 }
 
-static int gitdiff_hdrend(const char *line, struct patch *patch)
+static int gitdiff_hdrend(struct apply_state *state,
+			  const char *line,
+			  struct patch *patch)
 {
 	return -1;
 }
 
 /*
  * We're anal about diff header consistency, to make
