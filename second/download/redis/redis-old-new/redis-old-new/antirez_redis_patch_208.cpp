@@ -1605,7 +1605,7 @@ void clientCommand(client *c) {
         pauseClients(duration);
         addReply(c,shared.ok);
     } else {
-        addReplyError(c, "Syntax error, try CLIENT (LIST | KILL ip:port | GETNAME | SETNAME connection-name)");
+        addReplyError(c, "Syntax error, try CLIENT (LIST | KILL | GETNAME | SETNAME | PAUSE | REPLY)");
     }
 }
 