@@ -73,7 +73,8 @@ void onsig(int)
 
 }
 
-void CMakeErrorHandler(const char* message, const char* title, bool&, void* clientData)
+void CMakeMessageHandler(const char* message, const char* title, bool&,
+                         void* clientData)
 {
   cmCursesForm* self = static_cast<cmCursesForm*>( clientData );
   self->AddError(message, title);
@@ -171,7 +172,7 @@ int main(int argc, char const* const* argv)
     return 1;
     }
 
-  cmSystemTools::SetErrorCallback(CMakeErrorHandler, myform);
+  cmSystemTools::SetMessageCallback(CMakeMessageHandler, myform);
 
   cmCursesForm::CurrentForm = myform;
 