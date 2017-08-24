@@ -10,9 +10,8 @@ typedef struct
   char** Argv;
 } cmVTKWrapTclData;
 
-
 /* do almost everything in the initial pass */
-static int InitialPass(void *inf, void *mf, int argc, char *argv[])
+static int CCONV InitialPass(void *inf, void *mf, int argc, char *argv[])
 {
   char* file;
   char* str;
@@ -134,7 +133,7 @@ static int InitialPass(void *inf, void *mf, int argc, char *argv[])
   return 1;
 }
 
-static void FinalPass(void *inf, void *mf) 
+static void  CCONV FinalPass(void *inf, void *mf) 
 {
   cmLoadedCommandInfo *info = (cmLoadedCommandInfo *)inf;
   /* get our client data from initial pass */
@@ -146,8 +145,7 @@ static void FinalPass(void *inf, void *mf)
     fprintf(stderr,"*** Failed LOADED COMMAND Final Pass\n");
     }
 }
-
-static void Destructor(void *inf) 
+static void CCONV Destructor(void *inf) 
 {
   cmLoadedCommandInfo *info = (cmLoadedCommandInfo *)inf;
   /* get our client data from initial pass */
@@ -157,7 +155,7 @@ static void Destructor(void *inf)
 }
 
 #ifdef MUCHO_MUDSLIDE
-void CM_PLUGIN_EXPORT CMAKE_TEST_COMMANDInit(cmLoadedCommandInfo *info)
+void CM_PLUGIN_EXPORT CCONV CMAKE_TEST_COMMANDInit(cmLoadedCommandInfo *info)
 {
   info->InitialPass = InitialPass;
   info->FinalPass = FinalPass;