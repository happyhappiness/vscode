 			die("BUG: couldn't parse 'reset' as a color");
 		resetv.s = color;
 		append_atom(&resetv, &state);
 	}
 	if (state.stack->prev)
 		die(_("format: %%(end) atom missing"));
-	final_buf = &state.stack->output;
-	fwrite(final_buf->buf, 1, final_buf->len, stdout);
+	strbuf_addbuf(final_buf, &state.stack->output);
 	pop_stack_element(&state.stack);
+}
+
+void show_ref_array_item(struct ref_array_item *info, const char *format, int quote_style)
+{
+	struct strbuf final_buf = STRBUF_INIT;
+
+	format_ref_array_item(info, format, quote_style, &final_buf);
+	fwrite(final_buf.buf, 1, final_buf.len, stdout);
+	strbuf_release(&final_buf);
 	putchar('\n');
 }
 
 void pretty_print_ref(const char *name, const unsigned char *sha1,
 		const char *format)
 {
