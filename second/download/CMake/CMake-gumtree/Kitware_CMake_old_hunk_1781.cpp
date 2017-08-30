  fprintf(fout,"#include <string.h>\n");

  fprintf(fout,"#include \"Python.h\"\n\n");

  fprintf(fout,"// Handle compiler warning messages, etc.\n"

	  "#if defined( _MSC_VER ) && !defined(VTK_DISPLAY_WIN32_WARNINGS)\n"

	  "#pragma warning ( disable : 4706 )\n"

	  "#endif // Windows Warnings \n\n");



  for (i = 0; i < classes.size(); i++)

    {

