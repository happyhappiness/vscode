     return ! ( operator==(s) );
 }
 
 bool
 Ip::Address::operator <=(const Ip::Address &rhs) const
 {
-    if (IsAnyAddr() && !rhs.IsAnyAddr())
+    if (isAnyAddr() && !rhs.isAnyAddr())
         return true;
 
     return (matchIPAddr(rhs) <= 0);
 }
 
 bool
 Ip::Address::operator >=(const Ip::Address &rhs) const
 {
-    if (IsNoAddr() && !rhs.IsNoAddr())
+    if (isNoAddr() && !rhs.isNoAddr())
         return true;
 
     return ( matchIPAddr(rhs) >= 0);
 }
 
 bool
 Ip::Address::operator >(const Ip::Address &rhs) const
 {
-    if (IsNoAddr() && !rhs.IsNoAddr())
+    if (isNoAddr() && !rhs.isNoAddr())
         return true;
 
     return ( matchIPAddr(rhs) > 0);
 }
 
 bool
 Ip::Address::operator <(const Ip::Address &rhs) const
 {
-    if (IsAnyAddr() && !rhs.IsAnyAddr())
+    if (isAnyAddr() && !rhs.isAnyAddr())
         return true;
 
     return ( matchIPAddr(rhs) < 0);
 }
 
 unsigned short
-Ip::Address::GetPort() const
+Ip::Address::port() const
 {
-    return ntohs( m_SocketAddr.sin6_port );
+    return ntohs( mSocketAddr_.sin6_port );
 }
 
 unsigned short
-Ip::Address::SetPort(unsigned short prt)
+Ip::Address::port(unsigned short prt)
 {
-    m_SocketAddr.sin6_port = htons(prt);
+    mSocketAddr_.sin6_port = htons(prt);
 
     return prt;
 }
 
 /**
- * NtoA Given a buffer writes a readable ascii version of the IPA and/or port stored
+ * toStr Given a buffer writes a readable ascii version of the IPA and/or port stored
  *
  * Buffer must be of a size large enough to hold the converted address.
  * This size is provided in the form of a global defined variable MAX_IPSTRLEN
  * Should a buffer shorter be provided the string result will be truncated
  * at the length of the available buffer.
  *
  * A copy of the buffer is also returned for simple immediate display.
  */
 char *
-Ip::Address::NtoA(char* buf, const unsigned int blen, int force) const
+Ip::Address::toStr(char* buf, const unsigned int blen, int force) const
 {
     // Ensure we have a buffer.
     if (buf == NULL) {
         return NULL;
     }
 
     /* some external code may have blindly memset a parent. */
     /* thats okay, our default is known */
-    if ( IsAnyAddr() ) {
-        if (IsIPv6())
+    if ( isAnyAddr() ) {
+        if (isIPv6())
             memcpy(buf,"::\0", min(static_cast<unsigned int>(3),blen));
-        else if (IsIPv4())
+        else if (isIPv4())
             memcpy(buf,"0.0.0.0\0", min(static_cast<unsigned int>(8),blen));
         return buf;
     }
 
     memset(buf,0,blen); // clear buffer before write
 
     /* Pure-IPv6 CANNOT be displayed in IPv4 format. */
     /* However IPv4 CAN. */
-    if ( force == AF_INET && !IsIPv4() ) {
-        if ( IsIPv6() ) {
+    if ( force == AF_INET && !isIPv4() ) {
+        if ( isIPv6() ) {
             memcpy(buf, "{!IPv4}\0", min(static_cast<unsigned int>(8),blen));
         }
         return buf;
     }
 
-    if ( force == AF_INET6 || (force == AF_UNSPEC && IsIPv6()) ) {
+    if ( force == AF_INET6 || (force == AF_UNSPEC && isIPv6()) ) {
 
-        inet_ntop(AF_INET6, &m_SocketAddr.sin6_addr, buf, blen);
+        inet_ntop(AF_INET6, &mSocketAddr_.sin6_addr, buf, blen);
 
-    } else  if ( force == AF_INET || (force == AF_UNSPEC && IsIPv4()) ) {
+    } else  if ( force == AF_INET || (force == AF_UNSPEC && isIPv4()) ) {
 
         struct in_addr tmp;
-        GetInAddr(tmp);
+        getInAddr(tmp);
         inet_ntop(AF_INET, &tmp, buf, blen);
     } else {
         debugs(14, DBG_CRITICAL, "WARNING: Corrupt IP Address details OR required to display in unknown format (" <<
                force << "). accepted={" << AF_UNSPEC << "," << AF_INET << "," << AF_INET6 << "}");
         fprintf(stderr,"WARNING: Corrupt IP Address details OR required to display in unknown format (%d). accepted={%d,%d,%d} ",
                 force, AF_UNSPEC, AF_INET, AF_INET6);
