@@ -12,7 +12,7 @@
 #include "CMakeCommandLineInfo.h" 
 #include "../cmCacheManager.h"
 #include "../cmake.h"
-#include "../cmMakefileGenerator.h"
+#include "../cmGlobalGenerator.h"
 #ifdef _DEBUG
 #define new DEBUG_NEW
 #undef THIS_FILE
@@ -52,7 +52,7 @@ class CAboutDlg : public CDialog
 public:
   CAboutDlg();
 
-// Dialog Data
+  // Dialog Data
   //{{AFX_DATA(CAboutDlg)
   enum { IDD = IDD_ABOUTBOX };
   //}}AFX_DATA
@@ -146,7 +146,7 @@ CMakeSetupDialog::CMakeSetupDialog(const CMakeCommandLineInfo& cmdInfo,
 
   m_oldCX = -1;
   m_deltaXRemainder = 0;
-  m_CMakeInstance = 0;
+  m_CMakeInstance = new cmake;
 }
 
 void CMakeSetupDialog::DoDataExchange(CDataExchange* pDX)
@@ -184,15 +184,15 @@ BEGIN_MESSAGE_MAP(CMakeSetupDialog, CDialog)
   ON_CBN_SELCHANGE(IDC_WhereBuild, OnSelendokWhereBuild)
   ON_CBN_EDITCHANGE(IDC_WhereSource, OnChangeWhereSource)
   ON_CBN_SELENDOK(IDC_WhereSource, OnSelendokWhereSource)
-	ON_WM_SIZE()
+  ON_WM_SIZE()
   ON_WM_GETMINMAXINFO()
-	ON_BN_CLICKED(IDC_OK, OnOk)
-	ON_CBN_EDITCHANGE(IDC_Generator, OnEditchangeGenerator)
-	ON_BN_CLICKED(IDC_HELP_BUTTON, OnHelpButton)
+  ON_BN_CLICKED(IDC_OK, OnOk)
+  ON_CBN_EDITCHANGE(IDC_Generator, OnEditchangeGenerator)
+  ON_BN_CLICKED(IDC_HELP_BUTTON, OnHelpButton)
   ON_BN_CLICKED(IDCANCEL, OnCancel)
-	ON_BN_CLICKED(IDC_AdvancedValues, OnAdvancedValues)
-	ON_BN_DOUBLECLICKED(IDC_AdvancedValues, OnDoubleclickedAdvancedValues)
-	//}}AFX_MSG_MAP
+  ON_BN_CLICKED(IDC_AdvancedValues, OnAdvancedValues)
+  ON_BN_DOUBLECLICKED(IDC_AdvancedValues, OnDoubleclickedAdvancedValues)
+  //}}AFX_MSG_MAP
 END_MESSAGE_MAP()
 
 /////////////////////////////////////////////////////////////////////////////
@@ -245,7 +245,6 @@ BOOL CMakeSetupDialog::OnInitDialog()
   SetIcon(m_hIcon, FALSE);		// Set small icon
   // Load source and build dirs from registry
   this->LoadFromRegistry();
-  this->m_CMakeInstance = new cmake;
   std::vector<std::string> names;
   this->m_CMakeInstance->GetRegisteredGenerators(names);
   for(std::vector<std::string>::iterator i = names.begin();
@@ -266,8 +265,8 @@ BOOL CMakeSetupDialog::OnInitDialog()
     
   // Set the version number
   char tmp[1024];
-  sprintf(tmp,"Version %d.%d - %s", cmMakefile::GetMajorVersion(),
-          cmMakefile::GetMinorVersion(), cmMakefile::GetReleaseVersion());
+  sprintf(tmp,"Version %d.%d - %s", cmake::GetMajorVersion(),
+          cmake::GetMinorVersion(), cmake::GetReleaseVersion());
   SetDlgItemText(IDC_CMAKE_VERSION, tmp);
   this->UpdateData(FALSE);
   return TRUE;  // return TRUE  unless you set the focus to a control
@@ -560,38 +559,37 @@ void CMakeSetupDialog::RunCMake(bool generateProjectFiles)
   this->UpdateData();
   // always save the current gui values to disk
   this->SaveCacheFromGUI();
-  // free the old cmake and create a new one here
-  if (this->m_CMakeInstance)
-    {
-    delete this->m_CMakeInstance;
-    this->m_CMakeInstance = 0;
-    }
-  this->m_CMakeInstance = new cmake;
   // Make sure we are working from the cache on disk
   this->LoadCacheFromDiskToGUI(); 
   m_OKButton.EnableWindow(false);
-  // create the arguments for the cmake object
-  std::vector<std::string> args;
-  args.push_back((const char*)m_PathToExecutable);
-  std::string arg;
-  arg = "-H";
-  arg += m_WhereSource;
-  args.push_back(arg);
-  arg = "-B";
-  arg += m_WhereBuild;
-  args.push_back(arg);
-  arg = "-G";
-  arg += m_GeneratorChoiceString;
-  args.push_back(arg);
-  // run the generate process
-  if(this->m_CMakeInstance->Generate(args, generateProjectFiles) != 0)
+
+  // setup the cmake instance
+  if (generateProjectFiles)
     {
-    cmSystemTools::Error(
-      "Error in generation process, project files may be invalid");
+    if(m_CMakeInstance->Generate() != 0)
+      {
+      cmSystemTools::Error(
+        "Error in generation process, project files may be invalid");
+      }
     }
-  // update the GUI with any new values in the caused by the
-  // generation process
-  this->LoadCacheFromDiskToGUI();
+  else
+    {
+    m_CMakeInstance->SetHomeDirectory(m_WhereSource);
+    m_CMakeInstance->SetStartDirectory(m_WhereSource);
+    m_CMakeInstance->SetHomeOutputDirectory(m_WhereBuild);
+    m_CMakeInstance->SetStartOutputDirectory(m_WhereBuild);
+    m_CMakeInstance->SetGlobalGenerator(
+      m_CMakeInstance->CreateGlobalGenerator(m_GeneratorChoiceString));
+    if(m_CMakeInstance->Configure(m_PathToExecutable) != 0)
+      {
+      cmSystemTools::Error(
+        "Error in configuration process, project files may be invalid");
+      }
+    // update the GUI with any new values in the caused by the
+    // generation process
+    this->LoadCacheFromDiskToGUI();
+    }
+
   // save source and build paths to registry
   this->SaveToRegistry();
   // path is up-to-date now
@@ -647,6 +645,11 @@ void CMakeSetupDialog::OnChangeWhereBuild()
 
   std::string path = this->m_WhereBuild;
   cmSystemTools::ConvertToUnixSlashes(path);
+
+  // adjust the cmake instance
+  m_CMakeInstance->SetHomeOutputDirectory(m_WhereBuild);
+  m_CMakeInstance->SetStartOutputDirectory(m_WhereBuild);
+
   std::string cache_file = path;
   cache_file += "/CMakeCache.txt";
 