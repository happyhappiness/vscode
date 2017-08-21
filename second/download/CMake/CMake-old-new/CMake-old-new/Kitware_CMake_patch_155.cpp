@@ -675,7 +675,7 @@ int cmCursesMainForm::Generate()
   return 0;
 }
 
-void cmCursesMainForm::AddError(const char* message, const char*)
+void cmCursesMainForm::AddError(const char* message, const char* /*unused*/)
 {
   this->Errors.push_back(message);
 }
@@ -1028,7 +1028,7 @@ void cmCursesMainForm::HandleInput()
   }
 }
 
-int cmCursesMainForm::LoadCache(const char*)
+int cmCursesMainForm::LoadCache(const char* /*unused*/)
 
 {
   int r = this->CMakeInstance->LoadCache();