  

  fprintf(fout,"#include \"vtkTclUtil.h\"\n");

  

  fprintf(fout,

          "extern \"C\"\n"

          "{\n"

          "  typedef int (*vtkTclCommandType)(ClientData, Tcl_Interp *,int, char *[]);\n"

          "}\n"

          "\n");



  for (i = 0; i < classes.size(); i++)

    {

    fprintf(fout,"int %sCommand(ClientData cd, Tcl_Interp *interp,\n             int argc, char *argv[]);\n",classes[i].c_str());

