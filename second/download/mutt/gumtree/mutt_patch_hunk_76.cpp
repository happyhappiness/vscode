 
   if (hdr)
   {
     msg->flags.flagged = hdr->flagged;
     msg->flags.replied = hdr->replied;
     msg->flags.read    = hdr->read;
+    msg->received = hdr->received;
   }
+
+  if(msg->received == 0)
+    time(&msg->received);
   
   if (func (msg, dest, hdr) == 0)
   {
     if (dest->magic == M_MMDF)
       fputs (MMDF_SEP, msg->fp);
 
