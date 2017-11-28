#else
#define assert(EX)  ((EX)?((void)0):xassert("EX", __FILE__, __LINE__))
#endif

/* context-based debugging, the actual type is subject to change */
typedef int Ctx;
extern Ctx ctx_enter(const char *descr);
extern void ctx_exit(Ctx ctx);

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
