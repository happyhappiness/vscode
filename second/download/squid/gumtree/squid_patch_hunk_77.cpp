         if (tmp_line[tmp_line_len-1] == '\\') {
             debugs(3, 5, "parseConfigFile: tmp_line='" << tmp_line << "'");
             tmp_line[--tmp_line_len] = '\0';
             continue;
         }
 
+        trim_trailing_ws(tmp_line);
+        ProcessMacros(tmp_line, tmp_line_len);
         debugs(3, (opt_parse_cfg_only?1:5), "Processing: " << tmp_line);
 
-        /* Handle includes here */
-        if (tmp_line_len >= 9 && strncmp(tmp_line, "include", 7) == 0 && xisspace(tmp_line[7])) {
-            err_count += parseManyConfigFiles(tmp_line + 8, depth + 1);
-        } else if (!parse_line(tmp_line)) {
-            debugs(3, 0, HERE << cfg_filename << ":" << config_lineno << " unrecognized: '" << tmp_line << "'");
-            err_count++;
+        if (const char* expr = FindStatement(tmp_line, "if")) {
+            if_states.push_back(EvalBoolExpr(expr)); // store last if-statement meaning
+        } else if (FindStatement(tmp_line, "endif")) {
+            if (!if_states.empty())
+                if_states.pop_back(); // remove last if-statement meaning
+            else
+                fatalf("'endif' without 'if'\n");
+        } else if (FindStatement(tmp_line, "else")) {
+            if (!if_states.empty())
+                if_states.back() = !if_states.back();
+            else
+                fatalf("'else' without 'if'\n");
+        } else if (if_states.empty() || if_states.back()) { // test last if-statement meaning if present
+            /* Handle includes here */
+            if (tmp_line_len >= 9 && strncmp(tmp_line, "include", 7) == 0 && xisspace(tmp_line[7])) {
+                err_count += parseManyConfigFiles(tmp_line + 8, depth + 1);
+            } else if (!parse_line(tmp_line)) {
+                debugs(3, 0, HERE << cfg_filename << ":" << config_lineno << " unrecognized: '" << tmp_line << "'");
+                ++err_count;
+            }
         }
 
         safe_free(tmp_line);
         tmp_line_len = 0;
 
     }
+    if (!if_states.empty())
+        fatalf("if-statement without 'endif'\n");
 
     if (is_pipe) {
         int ret = pclose(fp);
 
         if (ret != 0)
             fatalf("parseConfigFile: '%s' failed with exit code %d\n", file_name, ret);
