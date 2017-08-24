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
@@ -64,7 +64,7 @@ class testFrame1 : public wxFrame
         {
         char buffer[200];
         sprintf(buffer, "Long, Long Label; this label should be "
-		"bigger than button %d",cc);
+                "bigger than button %d",cc);
         value = new wxStaticText(panel, -1, buffer);
         sizer->Add(value, 1, wxGROW | wxALL );
         sprintf(buffer, "Button %d", cc);
@@ -158,7 +158,7 @@ bool wxCMakeSetup::OnInit()
   frame->Show(TRUE);
   this->SetTopWindow(frame);
 
-  return TRUE;				       
+  return TRUE;                                 
 }
 
 int wxCMakeSetup::OnExit()