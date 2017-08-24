@@ -52,9 +52,10 @@ void onsig(int)
  
 }
 
-void CMakeErrorHandler(const char* message, const char* title, bool&)
+void CMakeErrorHandler(const char* message, const char* title, bool&, void* clientData)
 {
-  cmCursesForm::CurrentForm->AddError(message, title);
+  cmCursesForm* self = static_cast<cmCursesForm*>( clientData );
+  self->AddError(message, title);
 }
 
 int main(int argc, char** argv)
@@ -128,7 +129,7 @@ int main(int argc, char** argv)
   myform = new cmCursesMainForm(args, x);
   myform->LoadCache(cacheDir.c_str());
 
-  cmSystemTools::SetErrorCallback(CMakeErrorHandler);
+  cmSystemTools::SetErrorCallback(CMakeErrorHandler, myform);
 
   cmCursesForm::CurrentForm = myform;
 