    }
  
  fprintf(fout,"#include \"vtkTclUtil.h\"\n");
  fprintf(fout,"#include \"vtkVersion.h\"\n");
  fprintf(fout,"#define VTK_TCL_TO_STRING(x) VTK_TCL_TO_STRING0(x)\n");
  fprintf(fout,"#define VTK_TCL_TO_STRING0(x) #x\n");
  
  fprintf(fout,
          "extern \"C\"\n"
