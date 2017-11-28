 {
     debugs(11,5, HERE << "aborting transaction for " << reason <<
            "; " << serverConnection << ", this " << this);
     mustStop(reason);
 }
 
+HttpStateData::ReuseDecision::ReuseDecision(const StoreEntry *e, const Http::StatusCode code)
+    : answer(HttpStateData::ReuseDecision::reuseNot), reason(nullptr), entry(e), statusCode(code) {}
+
+HttpStateData::ReuseDecision::Answers
+HttpStateData::ReuseDecision::make(const HttpStateData::ReuseDecision::Answers ans, const char *why)
+{
+    answer = ans;
+    reason = why;
+    return answer;
+}
+
+std::ostream &operator <<(std::ostream &os, const HttpStateData::ReuseDecision &d)
+{
+    static const char *ReuseMessages[] = {
+        "do not cache and do not share", // reuseNot
+        "cache positively and share", // cachePositively
+        "cache negatively and share", // cacheNegatively
+        "do not cache but share" // doNotCacheButShare
+    };
+
+    assert(d.answer >= HttpStateData::ReuseDecision::reuseNot &&
+           d.answer <= HttpStateData::ReuseDecision::doNotCacheButShare);
+    return os << ReuseMessages[d.answer] << " because " << d.reason <<
+           "; HTTP status " << d.statusCode << " " << *(d.entry);
+}
+
