     va_end(args3);
 }
 
 static void
 _db_print_stderr(const char *format, va_list args)
 {
-    if (1 < Debug::level)
+    if (1 < Debug::Level())
         return;
 
     vfprintf(stderr, format, args);
 }
 
-std::ostream &
-Debug::getDebugOut()
-{
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
-}
-
 void
 Debug::parseOptions(char const *)
 {
     return;
 }
 
-void
-Debug::finishDebug()
+const char*
+SkipBuildPrefix(const char* path)
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
+    return path;
 }
 
-void
-Debug::xassert(const char *msg, const char *file, int line)
-{
+Debug::Context *Debug::Current = NULL;
 
-    if (CurrentDebug) {
-        *CurrentDebug << "assertion failed: " << file << ":" << line <<
-        ": \"" << msg << "\"";
-    }
-    abort();
+Debug::Context::Context(const int aSection, const int aLevel):
+    level(aLevel),
+    sectionLevel(Levels[aSection]),
+    upper(Current)
+{
+    buf.setf(std::ios::fixed);
+    buf.precision(2);
 }
 
-std::ostringstream *Debug::CurrentDebug (NULL);
+std::ostringstream &
+Debug::Start(const int section, const int level)
+{
+    Current = new Context(section, level);
+    return Current->buf;
+}
 
-const char*
-SkipBuildPrefix(const char* path)
+void
+Debug::Finish()
 {
-    return path;
+    if (Current) {
+        _db_print("%s\n", Current->buf.str().c_str());
+        delete Current;
+        Current = NULL;
+    }
 }
 
 std::ostream &
 Raw::print(std::ostream &os) const
 {
     if (label_)
