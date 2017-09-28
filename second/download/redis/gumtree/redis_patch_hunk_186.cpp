             if (!ch) {
                 json_set_token_error(token, json, "invalid escape code");
                 return;
             }
 
             /* Skip '\' */
-            json->index++;
+            json->ptr++;
         }
         /* Append normal character or translated single character
          * Unicode escapes are handled above */
         strbuf_append_char_unsafe(json->tmp, ch);
-        json->index++;
+        json->ptr++;
     }
-    json->index++;  /* Eat final quote (") */
+    json->ptr++;    /* Eat final quote (") */
 
     strbuf_ensure_null(json->tmp);
 
     token->type = T_STRING;
     token->value.string = strbuf_string(json->tmp, &token->string_len);
 }
