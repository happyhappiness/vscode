static int SystemToolsDebugReport(int, char* message, int*)
{
  fprintf(stderr, message);
  exit(1);
}