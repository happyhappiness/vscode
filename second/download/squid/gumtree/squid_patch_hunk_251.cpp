     if (doneWithAdaptation()) // we may still be receiving adapted response
         handleAdaptationCompleted();
 }
 
 // received adapted response headers (body may follow)
 void
-ServerStateData::noteAdaptationAnswer(HttpMsg *msg)
+ServerStateData::noteAdaptationAnswer(const Adaptation::Answer &answer)
 {
     clearAdaptation(adaptedHeadSource); // we do not expect more messages
 
+    switch (answer.kind) {
+    case Adaptation::Answer::akForward:
+        handleAdaptedHeader(answer.message);
+        break;
+
+    case Adaptation::Answer::akBlock:
+        handleAdaptationBlocked(answer);
+        break;
+
+    case Adaptation::Answer::akError:
+        handleAdaptationAborted(!answer.final);
+        break;
+    }
+}
+
+void
+ServerStateData::handleAdaptedHeader(HttpMsg *msg)
+{
     if (abortOnBadEntry("entry went bad while waiting for adapted headers")) {
         // If the adapted response has a body, the ICAP side needs to know
         // that nobody will consume that body. We will be destroyed upon
         // return. Tell the ICAP side that it is on its own.
         HttpReply *rep = dynamic_cast<HttpReply*>(msg);
         assert(rep);
