 		fprintf(o->file, "%s", header.buf);
 		strbuf_reset(&header);
 		goto free_ab_and_return;
 	} else if (!DIFF_OPT_TST(o, TEXT) &&
 	    ( (!textconv_one && diff_filespec_is_binary(one)) ||
 	      (!textconv_two && diff_filespec_is_binary(two)) )) {
+		if (!one->data && !two->data &&
+		    S_ISREG(one->mode) && S_ISREG(two->mode) &&
+		    !DIFF_OPT_TST(o, BINARY)) {
+			if (!hashcmp(one->sha1, two->sha1)) {
+				if (must_show_header)
+					fprintf(o->file, "%s", header.buf);
+				goto free_ab_and_return;
+			}
+			fprintf(o->file, "%s", header.buf);
+			fprintf(o->file, "%sBinary files %s and %s differ\n",
+				line_prefix, lbl[0], lbl[1]);
+			goto free_ab_and_return;
+		}
 		if (fill_mmfile(&mf1, one) < 0 || fill_mmfile(&mf2, two) < 0)
 			die("unable to read files to diff");
 		/* Quite common confusing case */
 		if (mf1.size == mf2.size &&
 		    !memcmp(mf1.ptr, mf2.ptr, mf1.size)) {
 			if (must_show_header)
