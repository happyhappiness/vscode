@@ -26,11 +26,11 @@ cmCursesStringWidget::cmCursesStringWidget(int width, int height,
                                            int left, int top) :
   cmCursesWidget(width, height, left, top)
 {
-  m_InEdit = false;
-  m_Type = cmCacheManager::STRING;
-  set_field_fore(m_Field,  A_NORMAL);
-  set_field_back(m_Field,  A_STANDOUT);
-  field_opts_off(m_Field,  O_STATIC);
+  this->InEdit = false;
+  this->Type = cmCacheManager::STRING;
+  set_field_fore(this->Field,  A_NORMAL);
+  set_field_back(this->Field,  A_STANDOUT);
+  field_opts_off(this->Field,  O_STATIC);
 }
 
 void cmCursesStringWidget::OnTab(cmCursesMainForm*, WINDOW*)
@@ -41,25 +41,25 @@ void cmCursesStringWidget::OnTab(cmCursesMainForm*, WINDOW*)
 void cmCursesStringWidget::OnReturn(cmCursesMainForm* fm, WINDOW*)
 {
   FORM* form = fm->GetForm();
-  if (m_InEdit)
+  if (this->InEdit)
     {
     cmCursesForm::LogMessage("String widget leaving edit.");
-    m_InEdit = false;
+    this->InEdit = false;
     fm->PrintKeys();
-    delete[] m_OriginalString;
+    delete[] this->OriginalString;
     // trick to force forms to update the field buffer
     form_driver(form, REQ_NEXT_FIELD);
     form_driver(form, REQ_PREV_FIELD);
-    m_Done = true;
+    this->Done = true;
     }
   else
     {
     cmCursesForm::LogMessage("String widget entering edit.");
-    m_InEdit = true;
+    this->InEdit = true;
     fm->PrintKeys();
-    char* buf = field_buffer(m_Field, 0);
-    m_OriginalString = new char[strlen(buf)+1];
-    strcpy(m_OriginalString, buf);
+    char* buf = field_buffer(this->Field, 0);
+    this->OriginalString = new char[strlen(buf)+1];
+    strcpy(this->OriginalString, buf);
     }
 }
 
@@ -75,18 +75,18 @@ bool cmCursesStringWidget::HandleInput(int& key, cmCursesMainForm* fm,
 
   FORM* form = fm->GetForm();
   // 10 == enter
-  if (!m_InEdit && ( key != 10 && key != KEY_ENTER ) )
+  if (!this->InEdit && ( key != 10 && key != KEY_ENTER ) )
     {
     return false;
     }
 
-  m_OriginalString=0;
-  m_Done = false;
+  this->OriginalString=0;
+  this->Done = false;
 
   char debugMessage[128];
 
   // <Enter> is used to change edit mode (like <Esc> in vi).
-  while(!m_Done)
+  while(!this->Done)
     {
     sprintf(debugMessage, "String widget handling input, key: %d", key);
     cmCursesForm::LogMessage(debugMessage);
@@ -111,7 +111,7 @@ bool cmCursesStringWidget::HandleInput(int& key, cmCursesMainForm* fm,
       }
 
     // If resize occured during edit, move out of edit mode
-    if (!m_InEdit && ( key != 10 && key != KEY_ENTER ) )
+    if (!this->InEdit && ( key != 10 && key != KEY_ENTER ) )
       {
       return false;
       }
@@ -125,8 +125,8 @@ bool cmCursesStringWidget::HandleInput(int& key, cmCursesMainForm* fm,
               key == KEY_NPAGE || key == ctrl('d') ||
               key == KEY_PPAGE || key == ctrl('u'))
       {
-      m_InEdit = false;
-      delete[] m_OriginalString;     
+      this->InEdit = false;
+      delete[] this->OriginalString;     
       // trick to force forms to update the field buffer
       form_driver(form, REQ_NEXT_FIELD);
       form_driver(form, REQ_PREV_FIELD);
@@ -135,12 +135,12 @@ bool cmCursesStringWidget::HandleInput(int& key, cmCursesMainForm* fm,
     // esc
     else if (key == 27)
       {
-      if (m_InEdit)
+      if (this->InEdit)
         {
-        m_InEdit = false;
+        this->InEdit = false;
         fm->PrintKeys();
-        this->SetString(m_OriginalString);
-        delete[] m_OriginalString;
+        this->SetString(this->OriginalString);
+        delete[] this->OriginalString;
         touchwin(w); 
         wrefresh(w); 
         return true;
@@ -182,7 +182,7 @@ bool cmCursesStringWidget::HandleInput(int& key, cmCursesMainForm* fm,
       {
       this->OnType(key, fm, w);
       }
-    if ( !m_Done )
+    if ( !this->Done )
       {
       touchwin(w); 
       wrefresh(w); 
@@ -205,7 +205,7 @@ const char* cmCursesStringWidget::GetString()
 
 const char* cmCursesStringWidget::GetValue()
 {
-  return field_buffer(m_Field, 0);
+  return field_buffer(this->Field, 0);
 }
 
 bool cmCursesStringWidget::PrintKeys()
@@ -217,7 +217,7 @@ bool cmCursesStringWidget::PrintKeys()
     {
     return false;
     }
-  if (m_InEdit)
+  if (this->InEdit)
     {
     char firstLine[512];
     // Clean the toolbar