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
@@ -274,9 +274,9 @@ bool cmVTKWrapTclCommand::WriteInit(const char *kitName,
     }
   
   fprintf(fout,"\n\nextern \"C\" {int VTK_EXPORT %s_SafeInit(Tcl_Interp *interp);}\n",
-	  kitName);
+          kitName);
   fprintf(fout,"\nextern \"C\" {int VTK_EXPORT %s_Init(Tcl_Interp *interp);}\n",
-	  kitName);
+          kitName);
   
   /* create an extern ref to the generic delete function */
   fprintf(fout,"\nextern void vtkTclGenericDeleteObject(ClientData cd);\n");
@@ -298,17 +298,17 @@ bool cmVTKWrapTclCommand::WriteInit(const char *kitName,
   if (!strcmp(kitName,"Vtkcommontcl"))
     {
     fprintf(fout,
-	    "  vtkTclInterpStruct *info = new vtkTclInterpStruct;\n");
+            "  vtkTclInterpStruct *info = new vtkTclInterpStruct;\n");
     fprintf(fout,
             "  info->Number = 0; info->InDelete = 0; info->DebugOn = 0;\n");
     fprintf(fout,"\n");
     fprintf(fout,"\n");
     fprintf(fout,
-	    "  Tcl_InitHashTable(&info->InstanceLookup, TCL_STRING_KEYS);\n");
+            "  Tcl_InitHashTable(&info->InstanceLookup, TCL_STRING_KEYS);\n");
     fprintf(fout,
-	    "  Tcl_InitHashTable(&info->PointerLookup, TCL_STRING_KEYS);\n");
+            "  Tcl_InitHashTable(&info->PointerLookup, TCL_STRING_KEYS);\n");
     fprintf(fout,
-	    "  Tcl_InitHashTable(&info->CommandLookup, TCL_STRING_KEYS);\n");
+            "  Tcl_InitHashTable(&info->CommandLookup, TCL_STRING_KEYS);\n");
     fprintf(fout,
             "  Tcl_SetAssocData(interp,(char *) \"vtk\",NULL,(ClientData *)info);\n");
     fprintf(fout,
@@ -329,7 +329,7 @@ bool cmVTKWrapTclCommand::WriteInit(const char *kitName,
   for (i = 0; i < classes.size(); i++)
     {
     fprintf(fout,"  vtkTclCreateNew(interp,(char *) \"%s\", %sNewCommand,\n",
-	    classes[i].c_str(), classes[i].c_str());
+            classes[i].c_str(), classes[i].c_str());
     fprintf(fout,"                  %sCommand);\n",classes[i].c_str());
     }
   