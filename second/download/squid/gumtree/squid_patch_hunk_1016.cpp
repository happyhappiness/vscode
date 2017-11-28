 }
 
 /// parse the PROXY/1.0 protocol header from the connection read buffer
 bool
 ConnStateData::parseProxy1p0()
 {
-    ::Parser::Tokenizer tok(in.buf);
+    ::Parser::Tokenizer tok(inBuf);
     tok.skip(Proxy1p0magic);
 
     // skip to first LF (assumes it is part of CRLF)
     static const CharacterSet lineContent = CharacterSet::LF.complement("non-LF");
     SBuf line;
     if (tok.prefix(line, lineContent, 107-Proxy1p0magic.length())) {
         if (tok.skip('\n')) {
             // found valid header
-            in.buf = tok.remaining();
+            inBuf = tok.remaining();
             needProxyProtocolHeader_ = false;
             // reset the tokenizer to work on found line only.
             tok.reset(line);
         } else
             return false; // no LF yet
 
     } else // protocol error only if there are more than 107 bytes prefix header
-        return proxyProtocolError(in.buf.length() > 107? "PROXY/1.0 error: missing CRLF" : NULL);
+        return proxyProtocolError(inBuf.length() > 107? "PROXY/1.0 error: missing CRLF" : NULL);
 
     static const SBuf unknown("UNKNOWN"), tcpName("TCP");
     if (tok.skip(tcpName)) {
 
         // skip TCP/IP version number
         static const CharacterSet tcpVersions("TCP-version","46");
