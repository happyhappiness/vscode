 		}
 
 		main_cmds.names[i]->len =
 			levenshtein(cmd, candidate, 0, 2, 1, 3) + 1;
 	}
 
-	qsort(main_cmds.names, main_cmds.cnt,
-	      sizeof(*main_cmds.names), levenshtein_compare);
+	QSORT(main_cmds.names, main_cmds.cnt, levenshtein_compare);
 
 	if (!main_cmds.cnt)
 		die(_("Uh oh. Your system reports no Git commands at all."));
 
 	/* skip and count prefix matches */
 	for (n = 0; n < main_cmds.cnt && !main_cmds.names[n]->len; n++)
