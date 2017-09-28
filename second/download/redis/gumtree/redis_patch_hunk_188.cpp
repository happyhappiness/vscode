     if (token->type == T_END) {
         return;
     }
 
     /* Found a known single character token, advance index and return */
     if (token->type != T_UNKNOWN) {
-        json->index++;
+        json->ptr++;
         return;
     }
 
-    /* Process characters which triggered T_UNKNOWN */
-    ch = json->data[json->index];
-
-    /* Must use strncmp() to match the front of the JSON string.
+    /* Process characters which triggered T_UNKNOWN
+     *
+     * Must use strncmp() to match the front of the JSON string.
      * JSON identifier must be lowercase.
      * When strict_numbers if disabled, either case is allowed for
      * Infinity/NaN (since we are no longer following the spec..) */
     if (ch == '"') {
         json_next_string_token(json, token);
         return;
     } else if (ch == '-' || ('0' <= ch && ch <= '9')) {
-        if (json->cfg->decode_refuse_badnum && json_is_invalid_number(json)) {
+        if (!json->cfg->decode_invalid_numbers && json_is_invalid_number(json)) {
             json_set_token_error(token, json, "invalid number");
             return;
         }
         json_next_number_token(json, token);
         return;
-    } else if (!strncmp(&json->data[json->index], "true", 4)) {
+    } else if (!strncmp(json->ptr, "true", 4)) {
         token->type = T_BOOLEAN;
         token->value.boolean = 1;
-        json->index += 4;
+        json->ptr += 4;
         return;
-    } else if (!strncmp(&json->data[json->index], "false", 5)) {
+    } else if (!strncmp(json->ptr, "false", 5)) {
         token->type = T_BOOLEAN;
         token->value.boolean = 0;
-        json->index += 5;
+        json->ptr += 5;
         return;
-    } else if (!strncmp(&json->data[json->index], "null", 4)) {
+    } else if (!strncmp(json->ptr, "null", 4)) {
         token->type = T_NULL;
-        json->index += 4;
+        json->ptr += 4;
         return;
-    } else if (!json->cfg->decode_refuse_badnum &&
+    } else if (json->cfg->decode_invalid_numbers &&
                json_is_invalid_number(json)) {
-        /* When refuse_badnum is disabled, only attempt to process
+        /* When decode_invalid_numbers is enabled, only attempt to process
          * numbers we know are invalid JSON (Inf, NaN, hex)
          * This is required to generate an appropriate token error,
          * otherwise all bad tokens will register as "invalid number"
          */
         json_next_number_token(json, token);
         return;
