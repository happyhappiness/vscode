static  CommandParser_t ConsoleHandler = {0, NULL, 0};
#define HANDLEDCOMMAND  0
#define NOTMYCOMMAND    1

static int show_settings = 0;

#if 0
#define DBPRINT0(s) printf(s)
#define DBPRINT1(s,v1) printf(s,v1)
#define DBPRINT2(s,v1,v2) printf(s,v1,v2)
#else
#define DBPRINT0(s)
#define DBPRINT1(s,v1)
