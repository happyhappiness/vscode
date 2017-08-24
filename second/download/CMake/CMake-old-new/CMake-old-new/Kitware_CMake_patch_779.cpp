@@ -1,5 +1,5 @@
 #include "cmCursesStringWidget.h"
-#include "cmCursesForm.h"
+#include "cmCursesMainForm.h"
 
 inline int ctrl(int z)
 {
@@ -18,8 +18,12 @@ cmCursesStringWidget::cmCursesStringWidget(int width, int height,
 }
 
 
-bool cmCursesStringWidget::HandleInput(int& key, FORM* form, WINDOW* w)
+bool cmCursesStringWidget::HandleInput(int& key, cmCursesMainForm* fm, 
+				       WINDOW* w)
 {
+  int x,y;
+
+  FORM* form = fm->GetForm();
   // 10 == enter
   if (!m_InEdit && ( key != 10 ) )
     {
@@ -35,6 +39,26 @@ bool cmCursesStringWidget::HandleInput(int& key, FORM* form, WINDOW* w)
     {
     sprintf(debugMessage, "String widget handling input, key: %d", key);
     cmCursesForm::LogMessage(debugMessage);
+
+    fm->PrintKeys();
+
+    getmaxyx(stdscr, y, x);
+    // If window too small, handle 'q' only
+    if ( x < cmCursesMainForm::MIN_WIDTH  || 
+	 y < cmCursesMainForm::MIN_HEIGHT )
+      {
+      // quit
+      if ( key == 'q' )
+	{
+	return false;
+	}
+      else
+	{
+	key=getch(); 
+	continue;
+	}
+      }
+
     // If resize occured during edit, move out of edit mode
     if (!m_InEdit && ( key != 10 && key != KEY_ENTER ) )
       {
@@ -47,6 +71,7 @@ bool cmCursesStringWidget::HandleInput(int& key, FORM* form, WINDOW* w)
 	{
 	cmCursesForm::LogMessage("String widget leaving edit.");
 	m_InEdit = false;
+	fm->PrintKeys();
 	delete[] originalStr;	
 	// trick to force forms to update the field buffer
 	form_driver(form, REQ_NEXT_FIELD);
@@ -57,6 +82,7 @@ bool cmCursesStringWidget::HandleInput(int& key, FORM* form, WINDOW* w)
 	{
 	cmCursesForm::LogMessage("String widget entering edit.");
 	m_InEdit = true;
+	fm->PrintKeys();
 	char* buf = field_buffer(m_Field, 0);
 	originalStr = new char[strlen(buf)+1];
 	strcpy(originalStr, buf);
@@ -80,6 +106,7 @@ bool cmCursesStringWidget::HandleInput(int& key, FORM* form, WINDOW* w)
       if (m_InEdit)
 	{
 	m_InEdit = false;
+	fm->PrintKeys();
 	this->SetString(originalStr);
 	delete[] originalStr;
 	touchwin(w); 
@@ -138,3 +165,41 @@ const char* cmCursesStringWidget::GetValue()
 {
   return field_buffer(m_Field, 0);
 }
+
+bool cmCursesStringWidget::PrintKeys()
+{
+  int x,y;
+  getmaxyx(stdscr, y, x);
+  if ( x < cmCursesMainForm::MIN_WIDTH  || 
+       y < cmCursesMainForm::MIN_HEIGHT )
+    {
+    return false;
+    }
+  if (m_InEdit)
+    {
+    char firstLine[512];
+    // Clean the toolbar
+    for(int i=0; i<512; i++)
+      {
+      firstLine[i] = ' ';
+      }
+    firstLine[511] = '\0';
+    curses_move(y-4,0);
+    printw(firstLine);
+    curses_move(y-3,0);
+    printw(firstLine);
+    curses_move(y-2,0);
+    printw(firstLine);
+    curses_move(y-1,0);
+    printw(firstLine);
+
+    sprintf(firstLine,  "Editing option, press [enter] to leave edit.");
+    curses_move(y-3,0);
+    printw(firstLine);
+    return true;
+    }
+  else
+    {
+    return false;
+    }
+}