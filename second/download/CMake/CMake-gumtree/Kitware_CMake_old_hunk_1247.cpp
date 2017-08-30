#include "cmQtAutomoc.h"





#define TRACE_LINE() printf(" %s %d\n", __PRETTY_FUNCTION__, __LINE__)



cmQtAutomoc::cmQtAutomoc()

:Verbose(true)

,RunMocFailed(false)

