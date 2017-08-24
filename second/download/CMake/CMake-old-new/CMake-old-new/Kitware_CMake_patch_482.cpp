@@ -242,7 +242,7 @@ void cmCursesMainForm::RePost()
   // Assign the fields: 3 for each entry: label, new entry marker
   // ('*' or ' ') and entry widget
   this->Fields = new FIELD*[3*this->NumberOfVisibleEntries+1];
-  int cc;
+  size_t cc;
   for ( cc = 0; cc < 3 * this->NumberOfVisibleEntries+1; cc ++ )
     {
     this->Fields[cc] = 0;
@@ -454,7 +454,7 @@ void cmCursesMainForm::PrintKeys(int process /* = 0 */)
   if (cw)
     {
     sprintf(firstLine, "Page %d of %d", cw->GetPage(), this->NumberOfPages);
-    curses_move(0,65-strlen(firstLine)-1);
+    curses_move(0,65-static_cast<unsigned int>(strlen(firstLine))-1);
     printw(firstLine);
     }
 //    }
@@ -526,10 +526,10 @@ void cmCursesMainForm::UpdateStatusBar(const char* message)
   // Join the key, help string and pad with spaces
   // (or truncate) as necessary
   char bar[cmCursesMainForm::MAX_WIDTH];
-  int i, curFieldLen = strlen(curField);
-  int helpLen = strlen(help);
+  size_t i, curFieldLen = strlen(curField);
+  size_t helpLen = strlen(help);
 
-  int width;
+  size_t width;
   if (x < cmCursesMainForm::MAX_WIDTH )
     {
     width = x;
@@ -592,7 +592,7 @@ void cmCursesMainForm::UpdateStatusBar(const char* message)
   char version[cmCursesMainForm::MAX_WIDTH];
   char vertmp[128];
   sprintf(vertmp,"CMake Version %s", cmVersion::GetCMakeVersion());
-  int sideSpace = (width-strlen(vertmp));
+  size_t sideSpace = (width-strlen(vertmp));
   for(i=0; i<sideSpace; i++) { version[i] = ' '; }
   sprintf(version+sideSpace, "%s", vertmp);
   version[width] = '\0';
@@ -795,8 +795,8 @@ void cmCursesMainForm::RemoveEntry(const char* value)
 // copy from the list box to the cache manager
 void cmCursesMainForm::FillCacheManagerFromUI()
 {   
-  int size = this->Entries->size();
-  for(int i=0; i < size; i++)
+  size_t size = this->Entries->size();
+  for(size_t i=0; i < size; i++)
     {
     cmCacheManager::CacheIterator it = 
       this->CMakeInstance->GetCacheManager()->GetCacheIterator(
@@ -866,7 +866,7 @@ void cmCursesMainForm::HandleInput()
       std::string searchstr = "Search: " + this->SearchString;
       this->UpdateStatusBar( searchstr.c_str() );
       this->PrintKeys(1);
-      curses_move(y-5,searchstr.size());
+      curses_move(y-5,static_cast<unsigned int>(searchstr.size()));
       //curses_move(1,1);
       touchwin(stdscr); 
       refresh();
@@ -961,7 +961,7 @@ void cmCursesMainForm::HandleInput()
       else if ( key == KEY_DOWN || key == ctrl('n') )
         {
         FIELD* cur = current_field(this->Form);
-        int findex = field_index(cur);
+        size_t findex = field_index(cur);
         if ( findex == 3*this->NumberOfVisibleEntries-1 )
           {
           continue;
@@ -1108,7 +1108,7 @@ void cmCursesMainForm::HandleInput()
         {
         this->OkToGenerate = false;
         FIELD* cur = current_field(this->Form);
-        int findex = field_index(cur);
+        size_t findex = field_index(cur);
 
         // make the next or prev. current field after deletion
         // each entry consists of fields: label, isnew, value
@@ -1199,7 +1199,7 @@ void cmCursesMainForm::JumpToCacheEntry(int idx, const char* astr)
     str = cmSystemTools::LowerCase(astr);
     }
 
-  if ( idx > this->NumberOfVisibleEntries )
+  if ( size_t(idx) > this->NumberOfVisibleEntries )
     {
     return;
     }
@@ -1232,7 +1232,7 @@ void cmCursesMainForm::JumpToCacheEntry(int idx, const char* astr)
           }
         }
       }
-    if ( findex >= 3* this->NumberOfVisibleEntries-1 )
+    if ( size_t(findex) >= 3* this->NumberOfVisibleEntries-1 )
       {
       set_current_field(this->Form, this->Fields[2]);
       }