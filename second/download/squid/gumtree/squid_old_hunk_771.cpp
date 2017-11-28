void ctx_exit(Ctx ctx);

/* defined debug section limits */
#define MAX_DEBUG_SECTIONS 100

/* defined names for Debug Levels */
#define DBG_CRITICAL	0	/**< critical messages always shown when they occur */
#define DBG_IMPORTANT	1	/**< important messages always shown when their section is being checked */
/* levels 2-8 are still being discussed amongst the developers */
#define DBG_DATA	9	/**< output is a large data dump only necessary for advanced debugging */

#define DBG_PARSE_NOTE(x) (opt_parse_cfg_only?0:(x)) /**< output is always to be displayed on '-k parse' but at level-x normally. */

class Debug
{

public:
    static char *debugOptions;
    static char *cache_log;
    static int rotateNumber;
    static int Levels[MAX_DEBUG_SECTIONS];
    static int level; ///< minimum debugging level required by debugs() call
    static int sectionLevel; ///< maximum debugging level allowed now
    static int override_X;
    static int log_stderr;
    static bool log_syslog;

    static std::ostream &getDebugOut();
    static void finishDebug();
    static void parseOptions(char const *);

private:
    // Hack: replaces global ::xassert() to debug debugging assertions
    static void xassert(const char *msg, const char *file, int line);

    static std::ostringstream *CurrentDebug;
    static int TheDepth; // level of nested debugging calls
};

extern FILE *debug_log;

size_t BuildPrefixInit();
const char * SkipBuildPrefix(const char* path);

/* Debug stream */
#define debugs(SECTION, LEVEL, CONTENT) \
   do { \
        if ((Debug::level = (LEVEL)) <= Debug::Levels[SECTION]) { \
            Debug::sectionLevel = Debug::Levels[SECTION]; \
            std::ostream &_dbo=Debug::getDebugOut(); \
            if (Debug::level > DBG_IMPORTANT) \
                _dbo << SkipBuildPrefix(__FILE__)<<"("<<__LINE__<<") "<<__FUNCTION__<<": "; \
            _dbo << CONTENT; \
            Debug::finishDebug(); \
        } \
   } while (/*CONSTCOND*/ 0)

/** stream manipulator which does nothing.
 * \deprecated Do not add to new code, and remove when editing old code
 *
