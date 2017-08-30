

static int SystemToolsDebugReport(int, char* message, int*)

{

  fprintf(stderr, "%s", message);

  fflush(stderr);

  return 1; // no further reporting required

}



void SystemTools::EnableMSVCDebugHook()

{

  if (getenv("DART_TEST_FROM_DART"))

    {

    _CrtSetReportHook(SystemToolsDebugReport);

    }

