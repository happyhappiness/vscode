 	if (first_tag) {
 		struct tag *tg;
 		fputc('\n', rpt);
 		fputs("Annotated Tags\n", rpt);
 		fputs("--------------\n", rpt);
 		for (tg = first_tag; tg; tg = tg->next_tag) {
-			fputs(sha1_to_hex(tg->sha1), rpt);
+			fputs(oid_to_hex(&tg->oid), rpt);
 			fputc(' ', rpt);
 			fputs(tg->name, rpt);
 			fputc('\n', rpt);
 		}
 	}
 
