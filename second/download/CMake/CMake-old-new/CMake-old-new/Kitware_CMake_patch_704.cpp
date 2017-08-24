@@ -826,18 +826,18 @@ static void suboption(struct connectdata *conn)
   struct SessionHandle *data = conn->data;
   struct TELNET *tn = (struct TELNET *)conn->proto.telnet;
 
-  printsub(data, '<', (unsigned char *)tn->subbuffer, SB_LEN(tn)+2);
+  printsub(data, '<', (unsigned char *)tn->subbuffer, (int)SB_LEN(tn)+2);
   switch (subchar = (unsigned char)SB_GET(tn)) {
     case TELOPT_TTYPE:
-      len = strlen(tn->subopt_ttype) + 4 + 2;
+      len = (int)strlen(tn->subopt_ttype) + 4 + 2;
       snprintf((char *)temp, sizeof(temp),
                "%c%c%c%c%s%c%c", IAC, SB, TELOPT_TTYPE,
                TELQUAL_IS, tn->subopt_ttype, IAC, SE);
       swrite(conn->firstsocket, (char*)temp, len);
       printsub(data, '>', &temp[2], len-2);
       break;
     case TELOPT_XDISPLOC:
-      len = strlen(tn->subopt_xdisploc) + 4 + 2;
+      len = (int)strlen(tn->subopt_xdisploc) + 4 + 2;
       snprintf((char *)temp, sizeof(temp),
                "%c%c%c%c%s%c%c", IAC, SB, TELOPT_XDISPLOC,
                TELQUAL_IS, tn->subopt_xdisploc, IAC, SE);
@@ -850,7 +850,7 @@ static void suboption(struct connectdata *conn)
       len = 4;
 
       for(v = tn->telnet_vars;v;v = v->next) {
-        tmplen = (strlen(v->data) + 1);
+        tmplen = (int)(strlen(v->data) + 1);
         /* Add the variable only if it fits */
         if(len + tmplen < (int)sizeof(temp)-6) {
           sscanf(v->data, "%127[^,],%s", varname, varval);