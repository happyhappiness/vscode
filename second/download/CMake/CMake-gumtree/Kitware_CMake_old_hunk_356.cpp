

/*--------------------------------------------------------------------------*/

/* VT100 escape sequence strings.  */

#define KWSYS_TERMINAL_VT100_NORMAL              "\33[0m"

#define KWSYS_TERMINAL_VT100_BOLD                "\33[1m"

#define KWSYS_TERMINAL_VT100_UNDERLINE           "\33[4m"

#define KWSYS_TERMINAL_VT100_BLINK               "\33[5m"

#define KWSYS_TERMINAL_VT100_INVERSE             "\33[7m"

#define KWSYS_TERMINAL_VT100_FOREGROUND_BLACK    "\33[30m"

#define KWSYS_TERMINAL_VT100_FOREGROUND_RED      "\33[31m"

#define KWSYS_TERMINAL_VT100_FOREGROUND_GREEN    "\33[32m"

#define KWSYS_TERMINAL_VT100_FOREGROUND_YELLOW   "\33[33m"

#define KWSYS_TERMINAL_VT100_FOREGROUND_BLUE     "\33[34m"

#define KWSYS_TERMINAL_VT100_FOREGROUND_MAGENTA  "\33[35m"

#define KWSYS_TERMINAL_VT100_FOREGROUND_CYAN     "\33[36m"

#define KWSYS_TERMINAL_VT100_FOREGROUND_WHITE    "\33[37m"

#define KWSYS_TERMINAL_VT100_BACKGROUND_BLACK    "\33[40m"

#define KWSYS_TERMINAL_VT100_BACKGROUND_RED      "\33[41m"

#define KWSYS_TERMINAL_VT100_BACKGROUND_GREEN    "\33[42m"

#define KWSYS_TERMINAL_VT100_BACKGROUND_YELLOW   "\33[43m"

#define KWSYS_TERMINAL_VT100_BACKGROUND_BLUE     "\33[44m"

#define KWSYS_TERMINAL_VT100_BACKGROUND_MAGENTA  "\33[45m"

#define KWSYS_TERMINAL_VT100_BACKGROUND_CYAN     "\33[46m"

#define KWSYS_TERMINAL_VT100_BACKGROUND_WHITE    "\33[47m"



/*--------------------------------------------------------------------------*/

/* Write VT100 escape sequences to the stream for the given color.  */

static void kwsysTerminalSetVT100Color(FILE* stream, int color)

{

  if(color == kwsysTerminal_Color_Normal)

    {

    fprintf(stream, KWSYS_TERMINAL_VT100_NORMAL);

    return;

    }



  switch(color & kwsysTerminal_Color_ForegroundMask)

    {

    case kwsysTerminal_Color_Normal:

      fprintf(stream, KWSYS_TERMINAL_VT100_NORMAL);

      break;

