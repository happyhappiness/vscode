 static BOOL
 match_ref(int offset, register const uschar *eptr, int length, match_data *md,
   unsigned long int ims)
 {
 const uschar *p = md->start_subject + md->offset_vector[offset];
 
-#ifdef DEBUG
-if (eptr >= md->end_subject)
-  printf("matching subject <null>");
-else
-  {
-  printf("matching subject ");
-  pchars(eptr, length, TRUE, md);
+#ifdef DEBUG
+if (eptr >= md->end_subject)
+  printf("matching subject <null>");
+else
+  {
+  printf("matching subject ");
+  pchars(eptr, length, TRUE, md);
+  }
+printf(" against backref ");
+pchars(p, length, FALSE, md);
+printf("\n");
+#endif
+
+/* Always fail if not enough characters left */
+
+if (length > md->end_subject - eptr) return FALSE;
+
+/* Separate the caselesss case for speed */
+
+if ((ims & PCRE_CASELESS) != 0)
+  {
+  while (length-- > 0)
+    if (md->lcc[*p++] != md->lcc[*eptr++]) return FALSE;
+  }
+else
+  { while (length-- > 0) if (*p++ != *eptr++) return FALSE; }
+
+return TRUE;
+}
+
+
+#ifdef SUPPORT_UTF8
+/*************************************************
+*       Match character against an XCLASS        *
+*************************************************/
+
+/* This function is called from within the XCLASS code below, to match a
+character against an extended class which might match values > 255.
+
+Arguments:
+  c           the character
+  data        points to the flag byte of the XCLASS data
+
+Returns:      TRUE if character matches, else FALSE
+*/
+
+static BOOL
+match_xclass(int c, const uschar *data)
+{
+int t;
+BOOL negated = (*data & XCL_NOT) != 0;
+
+/* Character values < 256 are matched against a bitmap, if one is present. If
+not, we still carry on, because there may be ranges that start below 256 in the
+additional data. */
+
+if (c < 256)
+  {
+  if ((*data & XCL_MAP) != 0 && (data[1 + c/8] & (1 << (c&7))) != 0)
+    return !negated;   /* char found */
+  }
+
+/* First skip the bit map if present. Then match against the list of Unicode
+properties or large chars or ranges that end with a large char. We won't ever
+encounter XCL_PROP or XCL_NOTPROP when UCP support is not compiled. */
+
+if ((*data++ & XCL_MAP) != 0) data += 32;
+
+while ((t = *data++) != XCL_END)
+  {
+  int x, y;
+  if (t == XCL_SINGLE)
+    {
+    GETCHARINC(x, data);
+    if (c == x) return !negated;
+    }
+  else if (t == XCL_RANGE)
+    {
+    GETCHARINC(x, data);
+    GETCHARINC(y, data);
+    if (c >= x && c <= y) return !negated;
+    }
+
+#ifdef SUPPORT_UCP
+  else  /* XCL_PROP & XCL_NOTPROP */
+    {
+    int chartype, othercase;
+    int rqdtype = *data++;
+    int category = ucp_findchar(c, &chartype, &othercase);
+    if (rqdtype >= 128)
+      {
+      if ((rqdtype - 128 == category) == (t == XCL_PROP)) return !negated;
+      }
+    else
+      {
+      if ((rqdtype == chartype) == (t == XCL_PROP)) return !negated;
+      }
+    }
+#endif  /* SUPPORT_UCP */
+  }
+
+return negated;   /* char did not match */
+}
+#endif
+
+
+/***************************************************************************
+****************************************************************************
+                   RECURSION IN THE match() FUNCTION
+
+The match() function is highly recursive. Some regular expressions can cause
+it to recurse thousands of times. I was writing for Unix, so I just let it
+call itself recursively. This uses the stack for saving everything that has
+to be saved for a recursive call. On Unix, the stack can be large, and this
+works fine.
+
+It turns out that on non-Unix systems there are problems with programs that
+use a lot of stack. (This despite the fact that every last chip has oodles
+of memory these days, and techniques for extending the stack have been known
+for decades.) So....
+
+There is a fudge, triggered by defining NO_RECURSE, which avoids recursive
+calls by keeping local variables that need to be preserved in blocks of memory
+obtained from malloc instead instead of on the stack. Macros are used to
+achieve this so that the actual code doesn't look very different to what it
+always used to.
+****************************************************************************
+***************************************************************************/
+
+
+/* These versions of the macros use the stack, as normal */
+
+#ifndef NO_RECURSE
+#define REGISTER register
+#define RMATCH(rx,ra,rb,rc,rd,re,rf,rg) rx = match(ra,rb,rc,rd,re,rf,rg)
+#define RRETURN(ra) return ra
+#else
+
+
+/* These versions of the macros manage a private stack on the heap. Note
+that the rd argument of RMATCH isn't actually used. It's the md argument of
+match(), which never changes. */
+
+#define REGISTER
+
+#define RMATCH(rx,ra,rb,rc,rd,re,rf,rg)\
+  {\
+  heapframe *newframe = (pcre_stack_malloc)(sizeof(heapframe));\
+  if (setjmp(frame->Xwhere) == 0)\
+    {\
+    newframe->Xeptr = ra;\
+    newframe->Xecode = rb;\
+    newframe->Xoffset_top = rc;\
+    newframe->Xims = re;\
+    newframe->Xeptrb = rf;\
+    newframe->Xflags = rg;\
+    newframe->Xprevframe = frame;\
+    frame = newframe;\
+    DPRINTF(("restarting from line %d\n", __LINE__));\
+    goto HEAP_RECURSE;\
+    }\
+  else\
+    {\
+    DPRINTF(("longjumped back to line %d\n", __LINE__));\
+    frame = md->thisframe;\
+    rx = frame->Xresult;\
+    }\
+  }
+
+#define RRETURN(ra)\
+  {\
+  heapframe *newframe = frame;\
+  frame = newframe->Xprevframe;\
+  (pcre_stack_free)(newframe);\
+  if (frame != NULL)\
+    {\
+    frame->Xresult = ra;\
+    md->thisframe = frame;\
+    longjmp(frame->Xwhere, 1);\
+    }\
+  return ra;\
   }
-printf(" against backref ");
-pchars(p, length, FALSE, md);
-printf("\n");
+
+
+/* Structure for remembering the local variables in a private frame */
+
+typedef struct heapframe {
+  struct heapframe *Xprevframe;
+
+  /* Function arguments that may change */
+
+  const uschar *Xeptr;
+  const uschar *Xecode;
+  int Xoffset_top;
+  long int Xims;
+  eptrblock *Xeptrb;
+  int Xflags;
+
+  /* Function local variables */
+
+  const uschar *Xcallpat;
+  const uschar *Xcharptr;
+  const uschar *Xdata;
+  const uschar *Xnext;
+  const uschar *Xpp;
+  const uschar *Xprev;
+  const uschar *Xsaved_eptr;
+
+  recursion_info Xnew_recursive;
+
+  BOOL Xcur_is_word;
+  BOOL Xcondition;
+  BOOL Xminimize;
+  BOOL Xprev_is_word;
+
+  unsigned long int Xoriginal_ims;
+
+#ifdef SUPPORT_UCP
+  int Xprop_type;
+  int Xprop_fail_result;
+  int Xprop_category;
+  int Xprop_chartype;
+  int Xprop_othercase;
+  int Xprop_test_against;
+  int *Xprop_test_variable;
 #endif
 
-/* Always fail if not enough characters left */
+  int Xctype;
+  int Xfc;
+  int Xfi;
+  int Xlength;
+  int Xmax;
+  int Xmin;
+  int Xnumber;
+  int Xoffset;
+  int Xop;
+  int Xsave_capture_last;
+  int Xsave_offset1, Xsave_offset2, Xsave_offset3;
+  int Xstacksave[REC_STACK_SAVE_MAX];
 
-if (length > md->end_subject - eptr) return FALSE;
+  eptrblock Xnewptrb;
 
-/* Separate the caselesss case for speed */
+  /* Place to pass back result, and where to jump back to */
 
-if ((ims & PCRE_CASELESS) != 0)
-  {
-  while (length-- > 0)
-    if (md->lcc[*p++] != md->lcc[*eptr++]) return FALSE;
-  }
-else
-  { while (length-- > 0) if (*p++ != *eptr++) return FALSE; }
+  int  Xresult;
+  jmp_buf Xwhere;
+
+} heapframe;
+
+#endif
 
-return TRUE;
-}
+
+/***************************************************************************
+***************************************************************************/
 
 
 
 /*************************************************
 *         Match from current position            *
 *************************************************/
 
 /* On entry ecode points to the first opcode, and eptr to the first character
 in the subject string, while eptrb holds the value of eptr at the start of the
 last bracketed group - used for breaking infinite loops matching zero-length
-strings.
+strings. This function is called recursively in many circumstances. Whenever it
+returns a negative (error) response, the outer incarnation must also return the
+same response.
+
+Performance note: It might be tempting to extract commonly used fields from the
+md structure (e.g. utf8, end_subject) into individual variables to improve
+performance. Tests using gcc on a SPARC disproved this; in the first case, it
+made performance worse.
 
 Arguments:
    eptr        pointer in subject
    ecode       position in code
    offset_top  current top pointer
    md          pointer to "static" info for the match
