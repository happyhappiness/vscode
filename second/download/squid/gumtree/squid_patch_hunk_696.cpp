 ACLIP::operator delete (void *address)
 {
     fatal ("ACLIP::operator delete: unused");
 }
 
 /**
- * Writes an IP ACL data into a buffer, then copies the buffer into the wordlist given
- *
- \param ip	ACL data structure to display
- \param state	wordlist structure which is being generated
- */
-void
-ACLIP::DumpIpListWalkee(acl_ip_data * const & ip, void *state)
-{
-    char tmpbuf[ ((MAX_IPSTRLEN*2)+6) ]; // space for 2 IPs and a CIDR mask(3) and seperators(3).
-    MemBuf mb;
-    wordlist **W = static_cast<wordlist **>(state);
-    tmpbuf[0] = '\0';
-
-    mb.init();
-    assert(mb.max_capacity > 0 && 1==1 );
-
-    ip->toStr(tmpbuf, sizeof(tmpbuf) );
-    assert(mb.max_capacity > 0 && 2==2 );
-    mb.append(tmpbuf, strlen(tmpbuf) );
-    assert(mb.max_capacity > 0 && 3==3);
-    wordlistAdd(W, mb.buf);
-    mb.clean();
-}
-
-/**
  * print/format an acl_ip_data structure for debugging output.
  *
- \param buf	string buffer to write to
- \param len	size of the buffer available
+ \param buf string buffer to write to
+ \param len size of the buffer available
  */
 void
 acl_ip_data::toStr(char *buf, int len) const
 {
     char *b1 = buf;
     char *b2 = NULL;
