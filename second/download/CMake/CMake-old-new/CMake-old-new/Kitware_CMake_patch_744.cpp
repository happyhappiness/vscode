@@ -33,6 +33,40 @@ cmCursesStringWidget::cmCursesStringWidget(int width, int height,
   field_opts_off(m_Field,  O_STATIC);
 }
 
+void cmCursesStringWidget::OnTab(cmCursesMainForm*, WINDOW*)
+{
+  //FORM* form = fm->GetForm();
+}
+
+void cmCursesStringWidget::OnReturn(cmCursesMainForm* fm, WINDOW*)
+{
+  FORM* form = fm->GetForm();
+  if (m_InEdit)
+    {
+    cmCursesForm::LogMessage("String widget leaving edit.");
+    m_InEdit = false;
+    fm->PrintKeys();
+    delete[] m_OriginalString;
+    // trick to force forms to update the field buffer
+    form_driver(form, REQ_NEXT_FIELD);
+    form_driver(form, REQ_PREV_FIELD);
+    m_Done = true;
+    }
+  else
+    {
+    cmCursesForm::LogMessage("String widget entering edit.");
+    m_InEdit = true;
+    fm->PrintKeys();
+    char* buf = field_buffer(m_Field, 0);
+    m_OriginalString = new char[strlen(buf)+1];
+    strcpy(m_OriginalString, buf);
+    }
+}
+
+void cmCursesStringWidget::OnType(int& key, cmCursesMainForm* fm, WINDOW* w)
+{
+  form_driver(fm->GetForm(), key);
+}
 
 bool cmCursesStringWidget::HandleInput(int& key, cmCursesMainForm* fm, 
                                        WINDOW* w)
@@ -46,12 +80,13 @@ bool cmCursesStringWidget::HandleInput(int& key, cmCursesMainForm* fm,
     return false;
     }
 
-  char* originalStr=0;
+  m_OriginalString=0;
+  m_Done = false;
 
   char debugMessage[128];
 
   // <Enter> is used to change edit mode (like <Esc> in vi).
-  while(1) 
+  while(!m_Done)
     {
     sprintf(debugMessage, "String widget handling input, key: %d", key);
     cmCursesForm::LogMessage(debugMessage);
@@ -83,34 +118,15 @@ bool cmCursesStringWidget::HandleInput(int& key, cmCursesMainForm* fm,
     // 10 == enter
     if (key == 10 || key == KEY_ENTER) 
       {
-      if (m_InEdit)
-        {
-        cmCursesForm::LogMessage("String widget leaving edit.");
-        m_InEdit = false;
-        fm->PrintKeys();
-        delete[] originalStr;   
-        // trick to force forms to update the field buffer
-        form_driver(form, REQ_NEXT_FIELD);
-        form_driver(form, REQ_PREV_FIELD);
-        return true;
-        }
-      else
-        {
-        cmCursesForm::LogMessage("String widget entering edit.");
-        m_InEdit = true;
-        fm->PrintKeys();
-        char* buf = field_buffer(m_Field, 0);
-        originalStr = new char[strlen(buf)+1];
-        strcpy(originalStr, buf);
-        }
+      this->OnReturn(fm, w);
       }
     else if ( key == KEY_DOWN || key == ctrl('n') ||
               key == KEY_UP || key == ctrl('p') ||
               key == KEY_NPAGE || key == ctrl('d') ||
               key == KEY_PPAGE || key == ctrl('u'))
       {
       m_InEdit = false;
-      delete[] originalStr;     
+      delete[] m_OriginalString;     
       // trick to force forms to update the field buffer
       form_driver(form, REQ_NEXT_FIELD);
       form_driver(form, REQ_PREV_FIELD);
@@ -123,13 +139,17 @@ bool cmCursesStringWidget::HandleInput(int& key, cmCursesMainForm* fm,
         {
         m_InEdit = false;
         fm->PrintKeys();
-        this->SetString(originalStr);
-        delete[] originalStr;
+        this->SetString(m_OriginalString);
+        delete[] m_OriginalString;
         touchwin(w); 
         wrefresh(w); 
         return true;
         }
       }
+    else if ( key == 9 )
+      {
+      this->OnTab(fm, w);
+      }
     else if ( key == KEY_LEFT || key == ctrl('b') )
       {
       form_driver(form, REQ_PREV_CHAR);
@@ -157,14 +177,17 @@ bool cmCursesStringWidget::HandleInput(int& key, cmCursesMainForm* fm,
       }
     else
       {
-      form_driver(form, key);
+      this->OnType(key, fm, w);
+      }
+    if ( !m_Done )
+      {
+      touchwin(w); 
+      wrefresh(w); 
+      
+      key=getch(); 
       }
-
-    touchwin(w); 
-    wrefresh(w); 
-
-    key=getch(); 
     }
+  return true;
 }
 
 void cmCursesStringWidget::SetString(const char* value)