             }
 
             ++cur;
             --l;
         }
 
-        goto done;
-    }
-
-    if (!*cur)
-        goto done;
-
-    ++cur;
+    } else if (*cur) {
 
-    // select quoting style for his particular token
-    switch (*cur) {
-
-    case '"':
-        quote = LOG_QUOTE_QUOTES;
         ++cur;
-        break;
 
-    case '\'':
-        quote = LOG_QUOTE_RAW;
-        ++cur;
-        break;
+        // select quoting style for his particular token
+        switch (*cur) {
 
-    case '[':
-        quote = LOG_QUOTE_MIMEBLOB;
-        ++cur;
-        break;
+        case '"':
+            quote = LOG_QUOTE_QUOTES;
+            ++cur;
+            break;
 
-    case '#':
-        quote = LOG_QUOTE_URL;
-        ++cur;
-        break;
+        case '\'':
+            quote = LOG_QUOTE_RAW;
+            ++cur;
+            break;
 
-    default:
-        quote = *quoting;
-        break;
-    }
+        case '[':
+            quote = LOG_QUOTE_MIMEBLOB;
+            ++cur;
+            break;
 
-    if (*cur == '-') {
-        left = true;
-        ++cur;
-    }
+        case '#':
+            quote = LOG_QUOTE_URL;
+            ++cur;
+            break;
 
-    if (*cur == '0') {
-        zero = true;
-        ++cur;
-    }
+        default:
+            quote = *quoting;
+            break;
+        }
 
-    char *endp;
-    if (xisdigit(*cur)) {
-        widthMin = strtol(cur, &endp, 10);
-        cur = endp;
-    }
+        if (*cur == '-') {
+            left = true;
+            ++cur;
+        }
 
-    if (*cur == '.' && xisdigit(*(++cur))) {
-        widthMax = strtol(cur, &endp, 10);
-        cur = endp;
-    }
+        if (*cur == '0') {
+            zero = true;
+            ++cur;
+        }
 
-    if (*cur == '{') {
-        char *cp;
-        ++cur;
-        l = strcspn(cur, "}");
-        cp = (char *)xmalloc(l + 1);
-        xstrncpy(cp, cur, l + 1);
-        data.string = cp;
-        cur += l;
+        char *endp;
+        if (xisdigit(*cur)) {
+            widthMin = strtol(cur, &endp, 10);
+            cur = endp;
+        }
 
-        if (*cur == '}')
+        if (*cur == '.' && xisdigit(*(++cur))) {
+            widthMax = strtol(cur, &endp, 10);
+            cur = endp;
+        }
+
+        if (*cur == '{') {
+            char *cp;
             ++cur;
-    }
+            l = strcspn(cur, "}");
+            cp = (char *)xmalloc(l + 1);
+            xstrncpy(cp, cur, l + 1);
+            data.string = cp;
+            cur += l;
 
-    type = LFT_NONE;
+            if (*cur == '}')
+                ++cur;
+        }
 
-    // Scan each registered token namespace
-    debugs(46, 9, HERE << "check for token in " << TheConfig.tokens.size() << " namespaces.");
-    for (std::list<TokenNamespace>::const_iterator itr = TheConfig.tokens.begin(); itr != TheConfig.tokens.end(); ++itr) {
-        debugs(46, 7, HERE << "check for possible " << itr->prefix << ":: token");
-        const size_t len = itr->prefix.size();
-        if (itr->prefix.cmp(cur, len) == 0 && cur[len] == ':' && cur[len+1] == ':') {
-            debugs(46, 5, HERE << "check for " << itr->prefix << ":: token in '" << cur << "'");
-            const char *old = cur;
-            cur = scanForToken(itr->tokenSet, cur+len+2);
-            if (old != cur) // found
-                break;
-            else // reset to start of namespace
-                cur = cur - len - 2;
+        type = LFT_NONE;
+
+        // Scan each registered token namespace
+        debugs(46, 9, HERE << "check for token in " << TheConfig.tokens.size() << " namespaces.");
+        for (std::list<TokenNamespace>::const_iterator itr = TheConfig.tokens.begin(); itr != TheConfig.tokens.end(); ++itr) {
+            debugs(46, 7, HERE << "check for possible " << itr->prefix << ":: token");
+            const size_t len = itr->prefix.size();
+            if (itr->prefix.cmp(cur, len) == 0 && cur[len] == ':' && cur[len+1] == ':') {
+                debugs(46, 5, HERE << "check for " << itr->prefix << ":: token in '" << cur << "'");
+                const char *old = cur;
+                cur = scanForToken(itr->tokenSet, cur+len+2);
+                if (old != cur) // found
+                    break;
+                else // reset to start of namespace
+                    cur = cur - len - 2;
+            }
         }
-    }
 
-    if (type == LFT_NONE) {
-        // For upward compatibility, assume "http::" prefix as default prefix
-        // for all log access formatting codes, except those starting with a
-        // "%" or a known namespace. (ie "icap::", "adapt::")
-        if (strncmp(cur,"http::", 6) == 0 && *(cur+6) != '%' )
-            cur += 6;
-
-        // NP: scan the sets of tokens in decreasing size to guarantee no
-        //     mistakes made with overlapping names. (Bug 3310)
-
-        // Scan for various long tokens
-        debugs(46, 5, HERE << "scan for possible Misc token");
-        cur = scanForToken(TokenTableMisc, cur);
-        // scan for 2-char tokens
         if (type == LFT_NONE) {
-            debugs(46, 5, HERE << "scan for possible 2C token");
-            cur = scanForToken(TokenTable2C, cur);
+            // For upward compatibility, assume "http::" prefix as default prefix
+            // for all log access formatting codes, except those starting with a
+            // "%" or a known namespace. (ie "icap::", "adapt::")
+            if (strncmp(cur,"http::", 6) == 0 && *(cur+6) != '%' )
+                cur += 6;
+
+            // NP: scan the sets of tokens in decreasing size to guarantee no
+            //     mistakes made with overlapping names. (Bug 3310)
+
+            // Scan for various long tokens
+            debugs(46, 5, HERE << "scan for possible Misc token");
+            cur = scanForToken(TokenTableMisc, cur);
+            // scan for 2-char tokens
+            if (type == LFT_NONE) {
+                debugs(46, 5, HERE << "scan for possible 2C token");
+                cur = scanForToken(TokenTable2C, cur);
+            }
+            // finally scan for 1-char tokens.
+            if (type == LFT_NONE) {
+                debugs(46, 5, HERE << "scan for possible 1C token");
+                cur = scanForToken(TokenTable1C, cur);
+            }
         }
-        // finally scan for 1-char tokens.
+
         if (type == LFT_NONE) {
-            debugs(46, 5, HERE << "scan for possible 1C token");
-            cur = scanForToken(TokenTable1C, cur);
+            fatalf("Can't parse configuration token: '%s'\n", def);
         }
-    }
-
-    if (type == LFT_NONE) {
-        fatalf("Can't parse configuration token: '%s'\n", def);
-    }
 
-    if (*cur == ' ') {
-        space = true;
-        ++cur;
+        if (*cur == ' ') {
+            space = true;
+            ++cur;
+        }
     }
 
-done:
-
     switch (type) {
 
 #if USE_ADAPTATION
     case LFT_ADAPTATION_LAST_HEADER:
 #endif
 
