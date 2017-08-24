@@ -8,6 +8,7 @@
 #include "CMakeCommandLineInfo.h" 
 #include "../cmCacheManager.h"
 #include "../cmake.h"
+#include "../cmMakefileGenerator.h"
 #ifdef _DEBUG
 #define new DEBUG_NEW
 #undef THIS_FILE
@@ -72,6 +73,7 @@ CMakeSetupDialog::CMakeSetupDialog(const CMakeCommandLineInfo& cmdInfo,
   //{{AFX_DATA_INIT(CMakeSetupDialog)
 	m_WhereSource = cmdInfo.m_WhereSource;
 	m_WhereBuild = cmdInfo.m_WhereBuild;
+	m_GeneratorChoiceString = _T("");
 	//}}AFX_DATA_INIT
   // Note that LoadIcon does not require a subsequent DestroyIcon in Win32
   m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
@@ -92,6 +94,7 @@ void CMakeSetupDialog::DoDataExchange(CDataExchange* pDX)
 {
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CMakeSetupDialog)
+	DDX_Control(pDX, IDC_Generator, m_GeneratorChoice);
 	DDX_Control(pDX, IDC_OK, m_OKButton);
 	DDX_Control(pDX, IDCANCEL, m_CancelButton);
 	DDX_CBStringExact(pDX, IDC_WhereSource, m_WhereSource);
@@ -103,6 +106,7 @@ void CMakeSetupDialog::DoDataExchange(CDataExchange* pDX)
 	DDX_Control(pDX, IDC_MouseHelpCaption, m_MouseHelp);
 	DDX_Control(pDX, IDC_CMAKE_VERSION, m_VersionDisplay);
 	DDX_Control(pDX, IDC_BuildProjects, m_Configure);
+	DDX_CBStringExact(pDX, IDC_Generator, m_GeneratorChoiceString);
 	//}}AFX_DATA_MAP
 }
 
@@ -120,8 +124,9 @@ BEGIN_MESSAGE_MAP(CMakeSetupDialog, CDialog)
   ON_CBN_SELENDOK(IDC_WhereSource, OnSelendokWhereSource)
 	ON_WM_SIZE()
   ON_WM_GETMINMAXINFO()
-  ON_BN_CLICKED(IDCANCEL, OnCancel)
 	ON_BN_CLICKED(IDC_OK, OnOk)
+  ON_BN_CLICKED(IDCANCEL, OnCancel)
+	ON_CBN_EDITCHANGE(IDC_Generator, OnEditchangeGenerator)
 	//}}AFX_MSG_MAP
 END_MESSAGE_MAP()
 
@@ -156,10 +161,22 @@ BOOL CMakeSetupDialog::OnInitDialog()
   SetIcon(m_hIcon, FALSE);		// Set small icon
   // Load source and build dirs from registry
   this->LoadFromRegistry();
+  cmake m; // force a register of generators
+  std::vector<std::string> names;
+  cmMakefileGenerator::GetRegisteredGenerators(names);
+  for(std::vector<std::string>::iterator i = names.begin();
+      i != names.end(); ++i)
+    {
+    m_GeneratorChoice.AddString(i->c_str());
+    }
+  m_GeneratorChoiceString = "Visual Studio 6";
+
   // try to load the cmake cache from disk
   this->LoadCacheFromDiskToGUI();
   m_WhereBuildControl.LimitText(2048);
   m_WhereSourceControl.LimitText(2048);
+  m_GeneratorChoice.LimitText(2048);
+    
   // Set the version number
   char tmp[1024];
   sprintf(tmp,"Version %d.%d", cmMakefile::GetMajorVersion(),
@@ -435,6 +452,9 @@ void CMakeSetupDialog::RunCMake(bool generateProjectFiles)
   arg = "-B";
   arg += m_WhereBuild;
   args.push_back(arg);
+  arg = "-G";
+  arg += m_GeneratorChoiceString;
+  args.push_back(arg);
   // run the generate process
   if(make.Generate(args, generateProjectFiles) != 0)
     {
@@ -617,6 +637,26 @@ void CMakeSetupDialog::LoadCacheFromDiskToGUI()
     {
     cmCacheManager::GetInstance()->LoadCache(m_WhereBuild);
     this->FillCacheGUIFromCacheManager();
+    if(cmCacheManager::GetInstance()->GetCacheEntry("CMAKE_GENERATOR"))
+      {
+      std::string curGen = 
+        cmCacheManager::GetInstance()->GetCacheEntry("CMAKE_GENERATOR")->m_Value;
+      if(m_GeneratorChoiceString != curGen.c_str())
+        {
+        m_GeneratorChoiceString = curGen.c_str();
+        this->UpdateData(FALSE);
+  //        m_GeneratorChoice.SetWindowText(m_GeneratorChoiceString); 
+//          int c = m_GeneratorChoice.GetCount();
+//          int j = m_GeneratorChoice.FindStringExact(0, curGen.c_str());
+//          if (j != CB_ERR)
+//            {
+//            m_GeneratorChoice.SetCurSel(j);
+//            }
+        
+//          m_GeneratorChoice.SelectString(0, curGen.c_str());
+//          this->UpdateData(FALSE);
+        }
+      }
     }
 }
 
@@ -735,3 +775,9 @@ void CMakeSetupDialog::OnOk()
   this->RunCMake(true);
   CDialog::OnOK();
 }
+
+void CMakeSetupDialog::OnEditchangeGenerator() 
+{
+	// TODO: Add your control notification handler code here
+	
+}