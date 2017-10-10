 void ref_array_sort(struct ref_sorting *sorting, struct ref_array *array)
 {
 	ref_sorting = sorting;
 	qsort(array->items, array->nr, sizeof(struct ref_array_item *), compare_refs);
 }
 
-static void print_value(struct atom_value *v, int quote_style)
-{
-	struct strbuf sb = STRBUF_INIT;
-	switch (quote_style) {
-	case QUOTE_NONE:
-		fputs(v->s, stdout);
-		break;
-	case QUOTE_SHELL:
-		sq_quote_buf(&sb, v->s);
-		break;
-	case QUOTE_PERL:
-		perl_quote_buf(&sb, v->s);
-		break;
-	case QUOTE_PYTHON:
-		python_quote_buf(&sb, v->s);
-		break;
-	case QUOTE_TCL:
-		tcl_quote_buf(&sb, v->s);
-		break;
-	}
-	if (quote_style != QUOTE_NONE) {
-		fputs(sb.buf, stdout);
-		strbuf_release(&sb);
-	}
-}
-
 static int hex1(char ch)
 {
 	if ('0' <= ch && ch <= '9')
 		return ch - '0';
 	else if ('a' <= ch && ch <= 'f')
 		return ch - 'a' + 10;
