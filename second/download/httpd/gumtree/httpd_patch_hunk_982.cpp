   If there isn't enough space in the offset vector, treat this as if it were a
   non-capturing bracket. Don't worry about setting the flag for the error case
   here; that is handled in the code for KET. */
 
   if (op > OP_BRA)
     {
-    int offset;
-    int number = op - OP_BRA;
+    number = op - OP_BRA;
 
     /* For extended extraction brackets (large number), we have to fish out the
     number from a dummy opcode at the start. */
 
-    if (number > EXTRACT_BASIC_MAX) number = (ecode[4] << 8) | ecode[5];
+    if (number > EXTRACT_BASIC_MAX)
+      number = GET2(ecode, 2+LINK_SIZE);
     offset = number << 1;
 
 #ifdef DEBUG
     printf("start bracket %d subject=", number);
     pchars(eptr, 16, TRUE, md);
     printf("\n");
 #endif
 
     if (offset < md->offset_max)
       {
-      int save_offset1 = md->offset_vector[offset];
-      int save_offset2 = md->offset_vector[offset+1];
-      int save_offset3 = md->offset_vector[md->offset_end - number];
+      save_offset1 = md->offset_vector[offset];
+      save_offset2 = md->offset_vector[offset+1];
+      save_offset3 = md->offset_vector[md->offset_end - number];
+      save_capture_last = md->capture_last;
 
       DPRINTF(("saving %d %d %d\n", save_offset1, save_offset2, save_offset3));
       md->offset_vector[md->offset_end - number] = eptr - md->start_subject;
 
       do
         {
-        if (match(eptr, ecode+3, offset_top, md, ims, eptrb, match_isgroup))
-          return TRUE;
-        ecode += (ecode[1] << 8) + ecode[2];
+        RMATCH(rrc, eptr, ecode + 1 + LINK_SIZE, offset_top, md, ims, eptrb,
+          match_isgroup);
+        if (rrc != MATCH_NOMATCH) RRETURN(rrc);
+        md->capture_last = save_capture_last;
+        ecode += GET(ecode, 1);
         }
       while (*ecode == OP_ALT);
 
       DPRINTF(("bracket %d failed\n", number));
 
       md->offset_vector[offset] = save_offset1;
       md->offset_vector[offset+1] = save_offset2;
       md->offset_vector[md->offset_end - number] = save_offset3;
 
-      return FALSE;
+      RRETURN(MATCH_NOMATCH);
       }
 
     /* Insufficient room for saving captured contents */
 
     else op = OP_BRA;
     }
