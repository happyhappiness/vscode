 
 /// parse the PROXY/2.0 protocol header from the connection read buffer
 bool
 ConnStateData::parseProxy2p0()
 {
     static const SBuf::size_type prefixLen = Proxy2p0magic.length();
-    if (in.buf.length() < prefixLen + 4)
+    if (inBuf.length() < prefixLen + 4)
         return false; // need more bytes
 
-    if ((in.buf[prefixLen] & 0xF0) != 0x20) // version == 2 is mandatory
+    if ((inBuf[prefixLen] & 0xF0) != 0x20) // version == 2 is mandatory
         return proxyProtocolError("PROXY/2.0 error: invalid version");
 
-    const char command = (in.buf[prefixLen] & 0x0F);
+    const char command = (inBuf[prefixLen] & 0x0F);
     if ((command & 0xFE) != 0x00) // values other than 0x0-0x1 are invalid
         return proxyProtocolError("PROXY/2.0 error: invalid command");
 
-    const char family = (in.buf[prefixLen+1] & 0xF0) >>4;
+    const char family = (inBuf[prefixLen+1] & 0xF0) >>4;
     if (family > 0x3) // values other than 0x0-0x3 are invalid
         return proxyProtocolError("PROXY/2.0 error: invalid family");
 
-    const char proto = (in.buf[prefixLen+1] & 0x0F);
+    const char proto = (inBuf[prefixLen+1] & 0x0F);
     if (proto > 0x2) // values other than 0x0-0x2 are invalid
         return proxyProtocolError("PROXY/2.0 error: invalid protocol type");
 
-    const char *clen = in.buf.rawContent() + prefixLen + 2;
+    const char *clen = inBuf.rawContent() + prefixLen + 2;
     uint16_t len;
     memcpy(&len, clen, sizeof(len));
     len = ntohs(len);
 
-    if (in.buf.length() < prefixLen + 4 + len)
+    if (inBuf.length() < prefixLen + 4 + len)
         return false; // need more bytes
 
-    in.buf.consume(prefixLen + 4); // 4 being the extra bytes
-    const SBuf extra = in.buf.consume(len);
+    inBuf.consume(prefixLen + 4); // 4 being the extra bytes
+    const SBuf extra = inBuf.consume(len);
     needProxyProtocolHeader_ = false; // found successfully
 
     // LOCAL connections do nothing with the extras
     if (command == 0x00/* LOCAL*/)
         return true;
 
