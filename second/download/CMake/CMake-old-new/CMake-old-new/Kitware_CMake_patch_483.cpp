@@ -454,7 +454,7 @@ void cmCursesMainForm::PrintKeys(int process /* = 0 */)
   if (cw)
     {
     sprintf(firstLine, "Page %d of %d", cw->GetPage(), this->NumberOfPages);
-    curses_move(0,65-strlen(firstLine)-1);
+    curses_move(0,65-static_cast<unsigned int>(strlen(firstLine))-1);
     printw(firstLine);
     }
 //    }
@@ -526,8 +526,8 @@ void cmCursesMainForm::UpdateStatusBar(const char* message)
   // Join the key, help string and pad with spaces
   // (or truncate) as necessary
   char bar[cmCursesMainForm::MAX_WIDTH];
-  int i, curFieldLen = strlen(curField);
-  int helpLen = strlen(help);
+  size_t i, curFieldLen = strlen(curField);
+  size_t helpLen = strlen(help);
 
   int width;
   if (x < cmCursesMainForm::MAX_WIDTH )
@@ -592,7 +592,7 @@ void cmCursesMainForm::UpdateStatusBar(const char* message)
   char version[cmCursesMainForm::MAX_WIDTH];
   char vertmp[128];
   sprintf(vertmp,"CMake Version %s", cmVersion::GetCMakeVersion());
-  int sideSpace = (width-strlen(vertmp));
+  size_t sideSpace = (width-strlen(vertmp));
   for(i=0; i<sideSpace; i++) { version[i] = ' '; }
   sprintf(version+sideSpace, "%s", vertmp);
   version[width] = '\0';
@@ -795,7 +795,7 @@ void cmCursesMainForm::RemoveEntry(const char* value)
 // copy from the list box to the cache manager
 void cmCursesMainForm::FillCacheManagerFromUI()
 {   
-  int size = this->Entries->size();
+  size_t size = this->Entries->size();
   for(int i=0; i < size; i++)
     {
     cmCacheManager::CacheIterator it = 
@@ -866,7 +866,7 @@ void cmCursesMainForm::HandleInput()
       std::string searchstr = "Search: " + this->SearchString;
       this->UpdateStatusBar( searchstr.c_str() );
       this->PrintKeys(1);
-      curses_move(y-5,searchstr.size());
+      curses_move(y-5,static_cast<unsigned int>(searchstr.size()));
       //curses_move(1,1);
       touchwin(stdscr); 
       refresh();