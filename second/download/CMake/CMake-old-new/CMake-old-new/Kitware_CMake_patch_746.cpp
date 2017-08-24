@@ -1,13 +1,13 @@
 /*=========================================================================
 
-  Program:   Insight Segmentation & Registration Toolkit
+  Program:   CMake - Cross-Platform Makefile Generator
   Module:    $RCSfile$
   Language:  C++
   Date:      $Date$
   Version:   $Revision$
 
-  Copyright (c) 2002 Insight Consortium. All rights reserved.
-  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.
+  Copyright (c) 2002 Kitware, Inc., Insight Consortium.  All rights reserved.
+  See Copyright.txt or http://www.cmake.org/HTML/Copyright.html for details.
 
      This software is distributed WITHOUT ANY WARRANTY; without even 
      the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
@@ -178,9 +178,9 @@ bool cmVTKWrapPythonCommand::WriteInit(const char *kitName,
   fprintf(fout,"#include <string.h>\n");
   fprintf(fout,"#include \"Python.h\"\n\n");
   fprintf(fout,"// Handle compiler warning messages, etc.\n"
-	  "#if defined( _MSC_VER ) && !defined(VTK_DISPLAY_WIN32_WARNINGS)\n"
-	  "#pragma warning ( disable : 4706 )\n"
-	  "#endif // Windows Warnings \n\n");
+          "#if defined( _MSC_VER ) && !defined(VTK_DISPLAY_WIN32_WARNINGS)\n"
+          "#pragma warning ( disable : 4706 )\n"
+          "#endif // Windows Warnings \n\n");
 
   for (i = 0; i < classes.size(); i++)
     {
@@ -192,7 +192,7 @@ bool cmVTKWrapPythonCommand::WriteInit(const char *kitName,
     }
 
   fprintf(fout,"\nstatic PyMethodDef Py%s_ClassMethods[] = {\n",
-	  kitName);
+          kitName);
   fprintf(fout,"{NULL, NULL, 0, NULL}};\n\n");
   
 #ifdef _WIN32
@@ -212,20 +212,20 @@ bool cmVTKWrapPythonCommand::WriteInit(const char *kitName,
   fprintf(fout,"  static char modulename[] = \"lib%s\";\n",kitName);
 #endif
   fprintf(fout,"  m = Py_InitModule(modulename, Py%s_ClassMethods);\n",
-	  kitName);
+          kitName);
   
   fprintf(fout,"  d = PyModule_GetDict(m);\n");
   fprintf(fout,"  if (!d) Py_FatalError(\"can't get dictionary for module %s!\");\n\n",
-	  kitName);
+          kitName);
 
   for (i = 0; i < classes.size(); i++)
     {
     fprintf(fout,"  if ((c = PyVTKClass_%sNew(modulename)))\n",
             classes[i].c_str());
     fprintf(fout,"    if (-1 == PyDict_SetItemString(d, \"%s\", c))\n",
-	    classes[i].c_str());
+            classes[i].c_str());
     fprintf(fout,"      Py_FatalError(\"can't add class %s to dictionary!\");\n\n",
-	    classes[i].c_str());
+            classes[i].c_str());
     }
   fprintf(fout,"}\n\n");
   fclose(fout);