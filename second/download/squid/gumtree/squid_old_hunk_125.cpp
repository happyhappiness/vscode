#else
#define assert(EX)  ((EX)?((void)0):xassert("EX", __FILE__, __LINE__))
#endif

/* context-based debugging, the actual type is subject to change */
typedef int Ctx;

/* defined debug section limits */
#define MAX_DEBUG_SECTIONS 100

/* defined names for Debug Levels */
#define DBG_CRITICAL	0	/**< critical messages always shown when they occur */
#define DBG_IMPORTANT	1	/**< important messages always shown when their section is being checked */
/* levels 2-8 are still being discussed amongst the developers */
#define DBG_DATA	9	/**< output is a large data dump only necessary for advanced debugging */

class Debug
{

public:
    static char *debugOptions;
    static char *cache_log;
