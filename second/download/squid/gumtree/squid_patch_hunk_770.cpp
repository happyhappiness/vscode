     if (ctx < 0 || ctx > CTX_MAX_LEVEL)
         return "<lost>";
 
     return Ctx_Descrs[ctx] ? Ctx_Descrs[ctx] : "<null>";
 }
 
-int Debug::TheDepth = 0;
+Debug::Context *Debug::Current = NULL;
 
-std::ostream &
-Debug::getDebugOut()
+Debug::Context::Context(const int aSection, const int aLevel):
+    level(aLevel),
+    sectionLevel(Levels[aSection]),
+    upper(Current)
 {
-    assert(TheDepth >= 0);
-    ++TheDepth;
-    if (TheDepth > 1) {
-        assert(CurrentDebug);
-        *CurrentDebug << std::endl << "reentrant debuging " << TheDepth << "-{";
-    } else {
-        assert(!CurrentDebug);
-        CurrentDebug = new std::ostringstream();
-        // set default formatting flags
-        CurrentDebug->setf(std::ios::fixed);
-        CurrentDebug->precision(2);
-    }
-    return *CurrentDebug;
+    formatStream();
 }
 
+/// Optimization: avoids new Context creation for every debugs().
 void
-Debug::finishDebug()
+Debug::Context::rewind(const int aSection, const int aLevel)
 {
-    assert(TheDepth >= 0);
-    assert(CurrentDebug);
-    if (TheDepth > 1) {
-        *CurrentDebug << "}-" << TheDepth << std::endl;
-    } else {
-        assert(TheDepth == 1);
-        _db_print("%s\n", CurrentDebug->str().c_str());
-        delete CurrentDebug;
-        CurrentDebug = NULL;
-    }
-    --TheDepth;
+    level = aLevel;
+    sectionLevel = Levels[aSection];
+    assert(upper == Current);
+
+    buf.str(std::string());
+    buf.clear();
+    // debugs() users are supposed to preserve format, but
+    // some do not, so we have to waste cycles resetting it for all.
+    formatStream();
 }
 
-// Hack: replaces global ::xassert() to debug debugging assertions
-// Relies on assert macro calling xassert() without a specific scope.
+/// configures default formatting for the debugging stream
 void
-Debug::xassert(const char *msg, const char *file, int line)
+Debug::Context::formatStream()
 {
+    const static std::ostringstream cleanStream;
+    buf.flags(cleanStream.flags() | std::ios::fixed);
+    buf.width(cleanStream.width());
+    buf.precision(2);
+    buf.fill(' ');
+    // If this is not enough, use copyfmt(cleanStream) which is ~10% slower.
+}
+
+std::ostringstream &
+Debug::Start(const int section, const int level)
+{
+    Context *future = NULL;
 
-    if (CurrentDebug) {
-        *CurrentDebug << "assertion failed: " << file << ":" << line <<
-        ": \"" << msg << "\"";
+    // prepare future context
+    if (Current) {
+        // all reentrant debugs() calls get here; create a dedicated context
+        future = new Context(section, level);
+    } else {
+        // Optimization: Nearly all debugs() calls get here; avoid allocations
+        static Context *topContext = new Context(1, 1);
+        topContext->rewind(section, level);
+        future = topContext;
     }
-    abort();
+
+    Current = future;
+
+    return future->buf;
 }
 
-std::ostringstream (*Debug::CurrentDebug)(NULL);
+void
+Debug::Finish()
+{
+    // TODO: Optimize to remove at least one extra copy.
+    _db_print("%s\n", Current->buf.str().c_str());
+
+    Context *past = Current;
+    Current = past->upper;
+    if (Current)
+        delete past;
+    // else it was a static topContext from Debug::Start()
+}
 
 size_t
 BuildPrefixInit()
 {
     // XXX: This must be kept in sync with the actual debug.cc location
     const char *ThisFileNameTail = "src/debug.cc";
