 	}
 
 	if (applied_pos >= 0) {
 		if (new_blank_lines_at_end &&
 		    preimage.nr + applied_pos >= img->nr &&
 		    (ws_rule & WS_BLANK_AT_EOF) &&
-		    ws_error_action != nowarn_ws_error) {
-			record_ws_error(WS_BLANK_AT_EOF, "+", 1,
+		    state->ws_error_action != nowarn_ws_error) {
+			record_ws_error(state, WS_BLANK_AT_EOF, "+", 1,
 					found_new_blank_lines_at_end);
-			if (ws_error_action == correct_ws_error) {
+			if (state->ws_error_action == correct_ws_error) {
 				while (new_blank_lines_at_end--)
 					remove_last_line(&postimage);
 			}
 			/*
 			 * We would want to prevent write_out_results()
 			 * from taking place in apply_patch() that follows
 			 * the callchain led us here, which is:
 			 * apply_patch->check_patch_list->check_patch->
 			 * apply_data->apply_fragments->apply_one_fragment
 			 */
-			if (ws_error_action == die_on_ws_error)
-				apply = 0;
+			if (state->ws_error_action == die_on_ws_error)
+				state->apply = 0;
 		}
 
-		if (apply_verbosely && applied_pos != pos) {
+		if (state->apply_verbosely && applied_pos != pos) {
 			int offset = applied_pos - pos;
-			if (apply_in_reverse)
+			if (state->apply_in_reverse)
 				offset = 0 - offset;
 			fprintf_ln(stderr,
 				   Q_("Hunk #%d succeeded at %d (offset %d line).",
 				      "Hunk #%d succeeded at %d (offset %d lines).",
 				      offset),
 				   nth_fragment, applied_pos + 1, offset);
