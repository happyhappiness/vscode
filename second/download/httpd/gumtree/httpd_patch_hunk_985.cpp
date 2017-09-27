   /* Or to a non-unique first char after study */
 
   else if (start_bits != NULL)
     {
     while (start_match < end_subject)
       {
-      register int c = *start_match;
+      register unsigned int c = *start_match;
       if ((start_bits[c/8] & (1 << (c&7))) == 0) start_match++; else break;
       }
     }
 
 #ifdef DEBUG  /* Sigh. Some compilers never learn. */
   printf(">>>> Match against: ");
   pchars(start_match, end_subject - start_match, TRUE, &match_block);
   printf("\n");
 #endif
 
-  /* If req_char is set, we know that that character must appear in the subject
-  for the match to succeed. If the first character is set, req_char must be
+  /* If req_byte is set, we know that that character must appear in the subject
+  for the match to succeed. If the first character is set, req_byte must be
   later in the subject; otherwise the test starts at the match point. This
   optimization can save a huge amount of backtracking in patterns with nested
-  unlimited repeats that aren't going to match. We don't know what the state of
-  case matching may be when this character is hit, so test for it in both its
-  cases if necessary. However, the different cased versions will not be set up
-  unless PCRE_CASELESS was given or the casing state changes within the regex.
-  Writing separate code makes it go faster, as does using an autoincrement and
-  backing off on a match. */
-
-  if (req_char >= 0)
+  unlimited repeats that aren't going to match. Writing separate code for
+  cased/caseless versions makes it go faster, as does using an autoincrement
+  and backing off on a match.
+
+  HOWEVER: when the subject string is very, very long, searching to its end can
+  take a long time, and give bad performance on quite ordinary patterns. This
+  showed up when somebody was matching /^C/ on a 32-megabyte string... so we
+  don't do this when the string is sufficiently long.
+
+  ALSO: this processing is disabled when partial matching is requested.
+  */
+
+  if (req_byte >= 0 &&
+      end_subject - start_match < REQ_BYTE_MAX &&
+      !match_block.partial)
     {
-    register const uschar *p = start_match + ((first_char >= 0)? 1 : 0);
+    register const uschar *p = start_match + ((first_byte >= 0)? 1 : 0);
 
     /* We don't need to repeat the search if we haven't yet reached the
     place we found it at last time. */
 
-    if (p > req_char_ptr)
+    if (p > req_byte_ptr)
       {
-      /* Do a single test if no case difference is set up */
-
-      if (req_char == req_char2)
+      if (req_byte_caseless)
         {
         while (p < end_subject)
           {
-          if (*p++ == req_char) { p--; break; }
+          register int pp = *p++;
+          if (pp == req_byte || pp == req_byte2) { p--; break; }
           }
         }
-
-      /* Otherwise test for either case */
-
       else
         {
         while (p < end_subject)
           {
-          register int pp = *p++;
-          if (pp == req_char || pp == req_char2) { p--; break; }
+          if (*p++ == req_byte) { p--; break; }
           }
         }
 
       /* If we can't find the required character, break the matching loop */
 
       if (p >= end_subject) break;
 
       /* If we have found the required character, save the point where we
       found it, so that we don't search again next time round the loop if
       the start hasn't passed this character yet. */
 
-      req_char_ptr = p;
+      req_byte_ptr = p;
       }
     }
 
   /* When a match occurs, substrings will be set for all internal extractions;
   we just need to set up the whole thing as substring 0 before returning. If
   there were too many extractions, set the return code to zero. In the case
   where we had to get some local store to hold offsets for backreferences, copy
   those back references that we can. In this case there need not be overflow
   if certain parts of the pattern were not used. */
 
   match_block.start_match = start_match;
-  if (!match(start_match, re->code, 2, &match_block, ims, NULL, match_isgroup))
+  match_block.match_call_count = 0;
+
+  rc = match(start_match, match_block.start_code, 2, &match_block, ims, NULL,
+    match_isgroup);
+
+  if (rc == MATCH_NOMATCH)
+    {
+    start_match++;
+#ifdef SUPPORT_UTF8
+    if (match_block.utf8)
+      while(start_match < end_subject && (*start_match & 0xc0) == 0x80)
+        start_match++;
+#endif
     continue;
+    }
+
+  if (rc != MATCH_MATCH)
+    {
+    DPRINTF((">>>> error: returning %d\n", rc));
+    return rc;
+    }
 
-  /* Copy the offset information from temporary store if necessary */
+  /* We have a match! Copy the offset information from temporary store if
+  necessary */
 
   if (using_temporary_offsets)
     {
     if (offsetcount >= 4)
       {
       memcpy(offsets + 2, match_block.offset_vector + 2,
