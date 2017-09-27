         }
 
       /* First, ensure the minimum number of matches are present. */
 
       for (i = 1; i <= min; i++)
         {
-        if (eptr >= md->end_subject) return FALSE;
-        GETCHARINC(c, eptr)         /* Get character; increment eptr */
-
-#ifdef SUPPORT_UTF8
-        /* We do not yet support class members > 255 */
-        if (c > 255) return FALSE;
-#endif
-
-        if ((data[c/8] & (1 << (c&7))) != 0) continue;
-        return FALSE;
+        if (eptr >= md->end_subject) RRETURN(MATCH_NOMATCH);
+        GETCHARINC(c, eptr);
+        if (!match_xclass(c, data)) RRETURN(MATCH_NOMATCH);
         }
 
       /* If max == min we can continue with the main loop without the
       need to recurse. */
 
       if (min == max) continue;
 
       /* If minimizing, keep testing the rest of the expression and advancing
       the pointer while it matches the class. */
 
       if (minimize)
         {
-        for (i = min;; i++)
+        for (fi = min;; fi++)
           {
-          if (match(eptr, ecode, offset_top, md, ims, eptrb, 0))
-            return TRUE;
-          if (i >= max || eptr >= md->end_subject) return FALSE;
-          GETCHARINC(c, eptr)       /* Get character; increment eptr */
-
-#ifdef SUPPORT_UTF8
-          /* We do not yet support class members > 255 */
-          if (c > 255) return FALSE;
-#endif
-          if ((data[c/8] & (1 << (c&7))) != 0) continue;
-          return FALSE;
+          RMATCH(rrc, eptr, ecode, offset_top, md, ims, eptrb, 0);
+          if (rrc != MATCH_NOMATCH) RRETURN(rrc);
+          if (fi >= max || eptr >= md->end_subject) RRETURN(MATCH_NOMATCH);
+          GETCHARINC(c, eptr);
+          if (!match_xclass(c, data)) RRETURN(MATCH_NOMATCH);
           }
         /* Control never gets here */
         }
 
       /* If maximizing, find the longest possible run, then work backwards. */
 
       else
         {
-        const uschar *pp = eptr;
-        int len = 1;
+        pp = eptr;
         for (i = min; i < max; i++)
           {
+          int len = 1;
           if (eptr >= md->end_subject) break;
-          GETCHARLEN(c, eptr, len)  /* Get character, set length if UTF-8 */
-
-#ifdef SUPPORT_UTF8
-          /* We do not yet support class members > 255 */
-          if (c > 255) break;
-#endif
-          if ((data[c/8] & (1 << (c&7))) == 0) break;
+          GETCHARLEN(c, eptr, len);
+          if (!match_xclass(c, data)) break;
           eptr += len;
           }
-
-        while (eptr >= pp)
+        for(;;)
           {
-          if (match(eptr--, ecode, offset_top, md, ims, eptrb, 0))
-            return TRUE;
-
-#ifdef SUPPORT_UTF8
+          RMATCH(rrc, eptr, ecode, offset_top, md, ims, eptrb, 0);
+          if (rrc != MATCH_NOMATCH) RRETURN(rrc);
+          if (eptr-- == pp) break;        /* Stop if tried at original pos */
           BACKCHAR(eptr)
-#endif
           }
-        return FALSE;
+        RRETURN(MATCH_NOMATCH);
         }
+
+      /* Control never gets here */
       }
-    /* Control never gets here */
+#endif    /* End of XCLASS */
+
+    /* Match a single character, casefully */
 
-    /* Match a run of characters */
+    case OP_CHAR:
+#ifdef SUPPORT_UTF8
+    if (md->utf8)
+      {
+      length = 1;
+      ecode++;
+      GETCHARLEN(fc, ecode, length);
+      if (length > md->end_subject - eptr) RRETURN(MATCH_NOMATCH);
+      while (length-- > 0) if (*ecode++ != *eptr++) RRETURN(MATCH_NOMATCH);
+      }
+    else
+#endif
 
-    case OP_CHARS:
+    /* Non-UTF-8 mode */
       {
-      register int length = ecode[1];
+      if (md->end_subject - eptr < 1) RRETURN(MATCH_NOMATCH);
+      if (ecode[1] != *eptr++) RRETURN(MATCH_NOMATCH);
       ecode += 2;
+      }
+    break;
 
-#ifdef DEBUG    /* Sigh. Some compilers never learn. */
-      if (eptr >= md->end_subject)
-        printf("matching subject <null> against pattern ");
-      else
-        {
-        printf("matching subject ");
-        pchars(eptr, length, TRUE, md);
-        printf(" against pattern ");
-        }
-      pchars(ecode, length, FALSE, md);
-      printf("\n");
-#endif
+    /* Match a single character, caselessly */
+
+    case OP_CHARNC:
+#ifdef SUPPORT_UTF8
+    if (md->utf8)
+      {
+      length = 1;
+      ecode++;
+      GETCHARLEN(fc, ecode, length);
+
+      if (length > md->end_subject - eptr) RRETURN(MATCH_NOMATCH);
+
+      /* If the pattern character's value is < 128, we have only one byte, and
+      can use the fast lookup table. */
 
-      if (length > md->end_subject - eptr) return FALSE;
-      if ((ims & PCRE_CASELESS) != 0)
+      if (fc < 128)
         {
-        while (length-- > 0)
-          if (md->lcc[*ecode++] != md->lcc[*eptr++])
-            return FALSE;
+        if (md->lcc[*ecode++] != md->lcc[*eptr++]) RRETURN(MATCH_NOMATCH);
         }
+
+      /* Otherwise we must pick up the subject character */
+
       else
         {
-        while (length-- > 0) if (*ecode++ != *eptr++) return FALSE;
+        int dc;
+        GETCHARINC(dc, eptr);
+        ecode += length;
+
+        /* If we have Unicode property support, we can use it to test the other
+        case of the character, if there is one. The result of ucp_findchar() is
+        < 0 if the char isn't found, and othercase is returned as zero if there
+        isn't one. */
+
+        if (fc != dc)
+          {
+#ifdef SUPPORT_UCP
+          int chartype;
+          int othercase;
+          if (ucp_findchar(fc, &chartype, &othercase) < 0 || dc != othercase)
+#endif
+            RRETURN(MATCH_NOMATCH);
+          }
         }
       }
+    else
+#endif   /* SUPPORT_UTF8 */
+
+    /* Non-UTF-8 mode */
+      {
+      if (md->end_subject - eptr < 1) RRETURN(MATCH_NOMATCH);
+      if (md->lcc[ecode[1]] != md->lcc[*eptr++]) RRETURN(MATCH_NOMATCH);
+      ecode += 2;
+      }
     break;
 
     /* Match a single character repeatedly; different opcodes share code. */
 
     case OP_EXACT:
-    min = max = (ecode[1] << 8) + ecode[2];
+    min = max = GET2(ecode, 1);
     ecode += 3;
     goto REPEATCHAR;
 
     case OP_UPTO:
     case OP_MINUPTO:
     min = 0;
-    max = (ecode[1] << 8) + ecode[2];
+    max = GET2(ecode, 1);
     minimize = *ecode == OP_MINUPTO;
     ecode += 3;
     goto REPEATCHAR;
 
     case OP_STAR:
     case OP_MINSTAR:
