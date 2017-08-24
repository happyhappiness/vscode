@@ -450,32 +450,35 @@ void cmCursesMainForm::UpdateStatusBar()
   FIELD* cur = current_field(m_Form);
   int index = field_index(cur);
   cmCursesWidget* lbl = reinterpret_cast<cmCursesWidget*>(field_userptr(
-    m_Fields[index-2]));
-  const char* curField = lbl->GetValue();
-
-  // Get the help string of the current entry
-  // and add it to the help string
-  char help[128];
-  cmCacheManager::CacheIterator it = 
-    this->m_CMakeInstance->GetCacheManager()->GetCacheIterator(curField);
-  if (!it.IsAtEnd())
+                                                            m_Fields[index-2]));
+  char help[128] = "";
+  const char* curField = "";
+  if ( lbl )
     {
-    const char* hs = it.GetProperty("HELPSTRING");
-    if ( hs )
+    curField = lbl->GetValue();
+    
+    // Get the help string of the current entry
+    // and add it to the help string
+    cmCacheManager::CacheIterator it = 
+      this->m_CMakeInstance->GetCacheManager()->GetCacheIterator(curField);
+    if (!it.IsAtEnd())
       {
-      strncpy(help, hs, 127);
-      help[127] = '\0';
+      const char* hs = it.GetProperty("HELPSTRING");
+      if ( hs )
+        {
+        strncpy(help, hs, 127);
+        help[127] = '\0';
+        }
+      else
+        {
+        help[0] = 0;
+        }
       }
     else
       {
-      help[0] = 0;
+      sprintf(help," ");
       }
     }
-  else
-    {
-    sprintf(help," ");
-    }
-
 
   // Join the key, help string and pad with spaces
   // (or truncate) as necessary
@@ -505,15 +508,15 @@ void cmCursesMainForm::UpdateStatusBar()
     if (curFieldLen + helpLen + 2 >= width)
       {
       strncpy(bar+curFieldLen+2, help, width
-	- curFieldLen - 2);
+              - curFieldLen - 2);
       }
     else
       {
       strcpy(bar+curFieldLen+2, help);
       for(i=curFieldLen+helpLen+2; i < width; ++i) 
-	{ 
-	bar[i] = ' '; 
-	}
+        { 
+        bar[i] = ' '; 
+        }
       }
     }
 