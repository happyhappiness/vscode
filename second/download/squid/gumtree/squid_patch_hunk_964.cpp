         debugs(29, 5, "Assembled line to send :" << mb.content());
         return mb.content();
     }
     return NULL;
 }
 
+void
+Auth::UserRequest::denyMessageFromHelper(const char *proto, const Helper::Reply &reply)
+{
+    static SBuf messageNote;
+    messageNote = SBuf(reply.notes.find("message"));
+    if (messageNote.isEmpty()) {
+        messageNote.append(proto);
+        messageNote.append(" Authentication denied with no reason given");
+    }
+    setDenyMessage(messageNote.c_str());
+}
+
