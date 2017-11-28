 void ctx_exit(Ctx ctx);
 
 /* defined debug section limits */
 #define MAX_DEBUG_SECTIONS 100
 
 /* defined names for Debug Levels */
-#define DBG_CRITICAL	0	/**< critical messages always shown when they occur */
-#define DBG_IMPORTANT	1	/**< important messages always shown when their section is being checked */
+#define DBG_CRITICAL    0   /**< critical messages always shown when they occur */
+#define DBG_IMPORTANT   1   /**< important messages always shown when their section is being checked */
 /* levels 2-8 are still being discussed amongst the developers */
-#define DBG_DATA	9	/**< output is a large data dump only necessary for advanced debugging */
+#define DBG_DATA    9   /**< output is a large data dump only necessary for advanced debugging */
 
 #define DBG_PARSE_NOTE(x) (opt_parse_cfg_only?0:(x)) /**< output is always to be displayed on '-k parse' but at level-x normally. */
 
 class Debug
 {
 
 public:
+    /// meta-information for debugs() or a similar debugging call
+    class Context
+    {
+    public:
+        Context(const int aSectionLevel, const int aLevel);
+
+        int level; ///< minimum debugging level required by the debugs() call
+        int sectionLevel; ///< maximum debugging level allowed during the call
+
+    private:
+        friend class Debug;
+        void rewind(const int aSection, const int aLevel);
+        void formatStream();
+        Context *upper; ///< previous or parent record in nested debugging calls
+        std::ostringstream buf; ///< debugs() output sink
+    };
+
+    /// whether debugging the given section and the given level produces output
+    static bool Enabled(const int section, const int level)
+    {
+        return level <= Debug::Levels[section];
+    }
+
     static char *debugOptions;
     static char *cache_log;
     static int rotateNumber;
     static int Levels[MAX_DEBUG_SECTIONS];
-    static int level; ///< minimum debugging level required by debugs() call
-    static int sectionLevel; ///< maximum debugging level allowed now
     static int override_X;
     static int log_stderr;
     static bool log_syslog;
 
-    static std::ostream &getDebugOut();
-    static void finishDebug();
     static void parseOptions(char const *);
 
-private:
-    // Hack: replaces global ::xassert() to debug debugging assertions
-    static void xassert(const char *msg, const char *file, int line);
+    /// minimum level required by the current debugs() call
+    static int Level() { return Current ? Current->level : 1; }
+    /// maximum level currently allowed
+    static int SectionLevel() { return Current ? Current->sectionLevel : 1; }
+
+    /// opens debugging context and returns output buffer
+    static std::ostringstream &Start(const int section, const int level);
+    /// logs output buffer created in Start() and closes debugging context
+    static void Finish();
 
-    static std::ostringstream *CurrentDebug;
-    static int TheDepth; // level of nested debugging calls
+private:
+    static Context *Current; ///< deepest active context; nil outside debugs()
 };
 
 extern FILE *debug_log;
 
 size_t BuildPrefixInit();
 const char * SkipBuildPrefix(const char* path);
 
 /* Debug stream */
 #define debugs(SECTION, LEVEL, CONTENT) \
    do { \
-        if ((Debug::level = (LEVEL)) <= Debug::Levels[SECTION]) { \
-            Debug::sectionLevel = Debug::Levels[SECTION]; \
-            std::ostream &_dbo=Debug::getDebugOut(); \
-            if (Debug::level > DBG_IMPORTANT) \
-                _dbo << SkipBuildPrefix(__FILE__)<<"("<<__LINE__<<") "<<__FUNCTION__<<": "; \
+        const int _dbg_level = (LEVEL); \
+        if (Debug::Enabled((SECTION), _dbg_level)) { \
+            std::ostream &_dbo = Debug::Start((SECTION), _dbg_level); \
+            if (_dbg_level > DBG_IMPORTANT) { \
+                _dbo << (SECTION) << ',' << _dbg_level << "| " \
+                     << SkipBuildPrefix(__FILE__)<<"("<<__LINE__<<") "<<__FUNCTION__<<": "; \
+            } \
             _dbo << CONTENT; \
-            Debug::finishDebug(); \
+            Debug::Finish(); \
         } \
    } while (/*CONSTCOND*/ 0)
 
 /** stream manipulator which does nothing.
  * \deprecated Do not add to new code, and remove when editing old code
  *
