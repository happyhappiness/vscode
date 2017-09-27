     have to replicate this bracket up to that many times. If brastackptr is
     0 this is an unmatched bracket which will generate an error, but take care
     not to try to access brastack[-1] when computing the length and restoring
     the branch_extra value. */
 
     case ')':
-    length += 3;
+    length += 1 + LINK_SIZE;
+    if (brastackptr > 0)
       {
-      int minval = 1;
-      int maxval = 1;
-      int duplength;
+      duplength = length - brastack[--brastackptr];
+      branch_extra = bralenstack[brastackptr];
+      }
+    else duplength = 0;
 
-      if (brastackptr > 0)
-        {
-        duplength = length - brastack[--brastackptr];
-        branch_extra = bralenstack[brastackptr];
-        }
-      else duplength = 0;
+    /* The following code is also used when a recursion such as (?3) is
+    followed by a quantifier, because in that case, it has to be wrapped inside
+    brackets so that the quantifier works. The value of duplength must be
+    set before arrival. */
 
-      /* Leave ptr at the final char; for read_repeat_counts this happens
-      automatically; for the others we need an increment. */
+    HANDLE_QUANTIFIED_BRACKETS:
 
-      if ((c = ptr[1]) == '{' && is_counted_repeat(ptr+2, &compile_block))
-        {
-        ptr = read_repeat_counts(ptr+2, &minval, &maxval, errorptr,
-          &compile_block);
-        if (*errorptr != NULL) goto PCRE_ERROR_RETURN;
-        }
-      else if (c == '*') { minval = 0; maxval = -1; ptr++; }
-      else if (c == '+') { maxval = -1; ptr++; }
-      else if (c == '?') { minval = 0; ptr++; }
-
-      /* If the minimum is zero, we have to allow for an OP_BRAZERO before the
-      group, and if the maximum is greater than zero, we have to replicate
-      maxval-1 times; each replication acquires an OP_BRAZERO plus a nesting
-      bracket set - hence the 7. */
+    /* Leave ptr at the final char; for read_repeat_counts this happens
+    automatically; for the others we need an increment. */
 
-      if (minval == 0)
-        {
-        length++;
-        if (maxval > 0) length += (maxval - 1) * (duplength + 7);
-        }
+    if ((c = ptr[1]) == '{' && is_counted_repeat(ptr+2))
+      {
+      ptr = read_repeat_counts(ptr+2, &min, &max, errorptr);
+      if (*errorptr != NULL) goto PCRE_ERROR_RETURN;
+      }
+    else if (c == '*') { min = 0; max = -1; ptr++; }
+    else if (c == '+') { min = 1; max = -1; ptr++; }
+    else if (c == '?') { min = 0; max = 1;  ptr++; }
+    else { min = 1; max = 1; }
+
+    /* If the minimum is zero, we have to allow for an OP_BRAZERO before the
+    group, and if the maximum is greater than zero, we have to replicate
+    maxval-1 times; each replication acquires an OP_BRAZERO plus a nesting
+    bracket set. */
+
+    if (min == 0)
+      {
+      length++;
+      if (max > 0) length += (max - 1) * (duplength + 3 + 2*LINK_SIZE);
+      }
 
-      /* When the minimum is greater than zero, 1 we have to replicate up to
-      minval-1 times, with no additions required in the copies. Then, if
-      there is a limited maximum we have to replicate up to maxval-1 times
-      allowing for a BRAZERO item before each optional copy and nesting
-      brackets for all but one of the optional copies. */
+    /* When the minimum is greater than zero, we have to replicate up to
+    minval-1 times, with no additions required in the copies. Then, if there
+    is a limited maximum we have to replicate up to maxval-1 times allowing
+    for a BRAZERO item before each optional copy and nesting brackets for all
+    but one of the optional copies. */
 
-      else
-        {
-        length += (minval - 1) * duplength;
-        if (maxval > minval)   /* Need this test as maxval=-1 means no limit */
-          length += (maxval - minval) * (duplength + 7) - 6;
-        }
+    else
+      {
+      length += (min - 1) * duplength;
+      if (max > min)   /* Need this test as max=-1 means no limit */
+        length += (max - min) * (duplength + 3 + 2*LINK_SIZE)
+          - (2 + 2*LINK_SIZE);
+      }
+
+    /* Allow space for once brackets for "possessive quantifier" */
+
+    if (ptr[1] == '+')
+      {
+      ptr++;
+      length += 2 + 2*LINK_SIZE;
       }
     continue;
 
-    /* Non-special character. For a run of such characters the length required
-    is the number of characters + 2, except that the maximum run length is 255.
-    We won't get a skipped space or a non-data escape or the start of a #
-    comment as the first character, so the length can't be zero. */
+    /* Non-special character. It won't be space or # in extended mode, so it is
+    always a genuine character. If we are in a \Q...\E sequence, check for the
+    end; if not, we have a literal. */
 
-    NORMAL_CHAR:
     default:
-    length += 2;
-    runlength = 0;
-    do
+    NORMAL_CHAR:
+
+    if (inescq && c == '\\' && ptr[1] == 'E')
       {
-      if ((options & PCRE_EXTENDED) != 0)
-        {
-        if ((compile_block.ctypes[c] & ctype_space) != 0) continue;
-        if (c == '#')
-          {
-          /* The space before the ; is to avoid a warning on a silly compiler
-          on the Macintosh. */
-          while ((c = *(++ptr)) != 0 && c != NEWLINE) ;
-          continue;
-          }
-        }
+      inescq = FALSE;
+      ptr++;
+      continue;
+      }
 
-      /* Backslash may introduce a data char or a metacharacter; stop the
-      string before the latter. */
+    length += 2;          /* For a one-byte character */
+    lastitemlength = 1;   /* Default length of last item for repeats */
 
-      if (c == '\\')
-        {
-        const uschar *saveptr = ptr;
-        c = check_escape(&ptr, errorptr, bracount, options, FALSE,
-          &compile_block);
-        if (*errorptr != NULL) goto PCRE_ERROR_RETURN;
-        if (c < 0) { ptr = saveptr; break; }
+    /* In UTF-8 mode, check for additional bytes. */
 
 #ifdef SUPPORT_UTF8
-        if (c > 127 && (options & PCRE_UTF8) != 0)
-          {
-          int i;
-          for (i = 0; i < sizeof(utf8_table1)/sizeof(int); i++)
-            if (c <= utf8_table1[i]) break;
-          runlength += i;
-          }
-#endif
+    if (utf8 && (c & 0xc0) == 0xc0)
+      {
+      while ((ptr[1] & 0xc0) == 0x80)         /* Can't flow over the end */
+        {                                     /* because the end is marked */
+        lastitemlength++;                     /* by a zero byte. */
+        length++;
+        ptr++;
         }
-
-      /* Ordinary character or single-char escape */
-
-      runlength++;
       }
+#endif
 
-    /* This "while" is the end of the "do" above. */
-
-    while (runlength < MAXLIT &&
-      (compile_block.ctypes[c = *(++ptr)] & ctype_meta) == 0);
-
-    ptr--;
-    length += runlength;
     continue;
     }
   }
 
-length += 4;    /* For final KET and END */
+length += 2 + LINK_SIZE;    /* For final KET and END */
+
+if ((options & PCRE_AUTO_CALLOUT) != 0)
+  length += 2 + 2*LINK_SIZE;  /* For final callout */
 
-if (length > 65539)
+if (length > MAX_PATTERN_SIZE)
   {
   *errorptr = ERR20;
   return NULL;
   }
 
 /* Compute the size of data block needed and get it, either from malloc or
-externally provided function. We specify "code[0]" in the offsetof() expression
-rather than just "code", because it has been reported that one broken compiler
-fails on "code" because it is also an independent variable. It should make no
-difference to the value of the offsetof(). */
+externally provided function. */
 
-size = length + offsetof(real_pcre, code[0]);
+size = length + sizeof(real_pcre) + name_count * (max_name_size + 3);
 re = (real_pcre *)(pcre_malloc)(size);
 
 if (re == NULL)
   {
   *errorptr = ERR21;
   return NULL;
   }
 
-/* Put in the magic number, and save the size, options, and table pointer */
+/* Put in the magic number, and save the sizes, options, and character table
+pointer. NULL is used for the default character tables. The nullpad field is at
+the end; it's there to help in the case when a regex compiled on a system with
+4-byte pointers is run on another with 8-byte pointers. */
 
 re->magic_number = MAGIC_NUMBER;
 re->size = size;
 re->options = options;
-re->tables = tables;
+re->dummy1 = re->dummy2 = 0;
+re->name_table_offset = sizeof(real_pcre);
+re->name_entry_size = max_name_size + 3;
+re->name_count = name_count;
+re->tables = (tables == pcre_default_tables)? NULL : tables;
+re->nullpad = NULL;
+
+/* The starting points of the name/number translation table and of the code are
+passed around in the compile data block. */
+
+compile_block.names_found = 0;
+compile_block.name_entry_size = max_name_size + 3;
+compile_block.name_table = (uschar *)re + re->name_table_offset;
+codestart = compile_block.name_table + re->name_entry_size * re->name_count;
+compile_block.start_code = codestart;
+compile_block.start_pattern = (const uschar *)pattern;
+compile_block.req_varyopt = 0;
+compile_block.nopartial = FALSE;
 
 /* Set up a starting, non-extracting bracket, then compile the expression. On
 error, *errorptr will be set non-NULL, so we don't need to look at the result
 of the function here. */
 
 ptr = (const uschar *)pattern;
-code = re->code;
+code = (uschar *)codestart;
 *code = OP_BRA;
 bracount = 0;
-(void)compile_regex(options, -1, &bracount, &code, &ptr, errorptr, FALSE, 0,
-  &reqchar, &countlits, &compile_block);
+(void)compile_regex(options, options & PCRE_IMS, &bracount, &code, &ptr,
+  errorptr, FALSE, 0, &firstbyte, &reqbyte, NULL, &compile_block);
 re->top_bracket = bracount;
-re->top_backref = top_backref;
+re->top_backref = compile_block.top_backref;
+
+if (compile_block.nopartial) re->options |= PCRE_NOPARTIAL;
 
 /* If not reached end of pattern on success, there's an excess bracket. */
 
 if (*errorptr == NULL && *ptr != 0) *errorptr = ERR22;
 
 /* Fill in the terminating state and check for disastrous overflow, but
 if debugging, leave the test till after things are printed out. */
 
 *code++ = OP_END;
 
 #ifndef DEBUG
-if (code - re->code > length) *errorptr = ERR23;
+if (code - codestart > length) *errorptr = ERR23;
 #endif
 
 /* Give an error if there's back reference to a non-existent capturing
 subpattern. */
 
-if (top_backref > re->top_bracket) *errorptr = ERR15;
+if (re->top_backref > re->top_bracket) *errorptr = ERR15;
 
-/* Failed to compile */
+/* Failed to compile, or error while post-processing */
 
 if (*errorptr != NULL)
   {
   (pcre_free)(re);
   PCRE_ERROR_RETURN:
   *erroroffset = ptr - (const uschar *)pattern;
   return NULL;
   }
 
-/* If the anchored option was not passed, set flag if we can determine that the
-pattern is anchored by virtue of ^ characters or \A or anything else (such as
-starting with .* when DOTALL is set).
+/* If the anchored option was not passed, set the flag if we can determine that
+the pattern is anchored by virtue of ^ characters or \A or anything else (such
+as starting with .* when DOTALL is set).
 
-Otherwise, see if we can determine what the first character has to be, because
-that speeds up unanchored matches no end. If not, see if we can set the
+Otherwise, if we know what the first character has to be, save it, because that
+speeds up unanchored matches no end. If not, see if we can set the
 PCRE_STARTLINE flag. This is helpful for multiline matches when all branches
 start with ^. and also when all branches start with .* for non-DOTALL matches.
 */
 
 if ((options & PCRE_ANCHORED) == 0)
   {
   int temp_options = options;
-  if (is_anchored(re->code, &temp_options))
+  if (is_anchored(codestart, &temp_options, 0, compile_block.backref_map))
     re->options |= PCRE_ANCHORED;
   else
     {
-    int ch = find_firstchar(re->code, &temp_options);
-    if (ch >= 0)
-      {
-      re->first_char = ch;
+    if (firstbyte < 0)
+      firstbyte = find_firstassertedchar(codestart, &temp_options, FALSE);
+    if (firstbyte >= 0)   /* Remove caseless flag for non-caseable chars */
+      {
+      int ch = firstbyte & 255;
+      re->first_byte = ((firstbyte & REQ_CASELESS) != 0 &&
+         compile_block.fcc[ch] == ch)? ch : firstbyte;
       re->options |= PCRE_FIRSTSET;
       }
-    else if (is_startline(re->code))
+    else if (is_startline(codestart, 0, compile_block.backref_map))
       re->options |= PCRE_STARTLINE;
     }
   }
 
-/* Save the last required character if there are at least two literal
-characters on all paths, or if there is no first character setting. */
+/* For an anchored pattern, we use the "required byte" only if it follows a
+variable length item in the regex. Remove the caseless flag for non-caseable
+bytes. */
 
-if (reqchar >= 0 && (countlits > 1 || (re->options & PCRE_FIRSTSET) == 0))
+if (reqbyte >= 0 &&
+     ((re->options & PCRE_ANCHORED) == 0 || (reqbyte & REQ_VARY) != 0))
   {
-  re->req_char = reqchar;
+  int ch = reqbyte & 255;
+  re->req_byte = ((reqbyte & REQ_CASELESS) != 0 &&
+    compile_block.fcc[ch] == ch)? (reqbyte & ~REQ_CASELESS) : reqbyte;
   re->options |= PCRE_REQCHSET;
   }
 
 /* Print out the compiled data for debugging */
 
 #ifdef DEBUG
 
 printf("Length = %d top_bracket = %d top_backref = %d\n",
   length, re->top_bracket, re->top_backref);
 
 if (re->options != 0)
   {
-  printf("%s%s%s%s%s%s%s%s%s\n",
+  printf("%s%s%s%s%s%s%s%s%s%s\n",
+    ((re->options & PCRE_NOPARTIAL) != 0)? "nopartial " : "",
     ((re->options & PCRE_ANCHORED) != 0)? "anchored " : "",
     ((re->options & PCRE_CASELESS) != 0)? "caseless " : "",
     ((re->options & PCRE_ICHANGED) != 0)? "case state changed " : "",
     ((re->options & PCRE_EXTENDED) != 0)? "extended " : "",
     ((re->options & PCRE_MULTILINE) != 0)? "multiline " : "",
     ((re->options & PCRE_DOTALL) != 0)? "dotall " : "",
