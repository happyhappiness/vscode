@@ -430,6 +430,7 @@ __archive_read_program(struct archive_read_filter *self, const char *cmd)
 	    &state->child_stdout);
 	if (child == -1) {
 		free(state->out_buf);
+		archive_string_free(&state->description);
 		free(state);
 		archive_set_error(&self->archive->archive, EINVAL,
 		    "Can't initialize filter; unable to run program \"%s\"",
@@ -441,6 +442,7 @@ __archive_read_program(struct archive_read_filter *self, const char *cmd)
 	if (state->child == NULL) {
 		child_stop(self, state);
 		free(state->out_buf);
+		archive_string_free(&state->description);
 		free(state);
 		archive_set_error(&self->archive->archive, EINVAL,
 		    "Can't initialize filter; unable to run program \"%s\"",