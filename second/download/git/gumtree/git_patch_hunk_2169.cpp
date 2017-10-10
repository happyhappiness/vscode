 		else if (skip_prefix(diffopts, "--unified=", &v))
 			xecfg.ctxlen = strtoul(v, NULL, 10);
 		else if (skip_prefix(diffopts, "-u", &v))
 			xecfg.ctxlen = strtoul(v, NULL, 10);
 		if (o->word_diff)
 			init_diff_words_data(&ecbdata, o, one, two);
-		xdi_diff_outf(&mf1, &mf2, fn_out_consume, &ecbdata,
-			      &xpp, &xecfg);
+		if (xdi_diff_outf(&mf1, &mf2, fn_out_consume, &ecbdata,
+				  &xpp, &xecfg))
+			die("unable to generate diff for %s", one->path);
 		if (o->word_diff)
 			free_diff_words_data(&ecbdata);
 		if (textconv_one)
 			free(mf1.ptr);
 		if (textconv_two)
 			free(mf2.ptr);
