@@ -171,8 +171,6 @@ void CMakeSetupDialog::DoDataExchange(CDataExchange* pDX)
 {
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CMakeSetupDialog)
-	DDX_Control(pDX, IDC_CMAKE_VERSION, m_VersionDisplay);
-	DDX_Control(pDX, IDC_PROGRESS, m_StatusDisplay);
 	DDX_Control(pDX, IDC_AdvancedValues, m_AdvancedValuesControl);
 	DDX_Control(pDX, IDC_BuildForLabel, m_BuildForLabel);
 	DDX_Control(pDX, IDC_BROWSE_SOURCE, m_BrowseSource);
@@ -188,6 +186,7 @@ void CMakeSetupDialog::DoDataExchange(CDataExchange* pDX)
 	DDX_Control(pDX, IDC_WhereBuild, m_WhereBuildControl);
 	DDX_Control(pDX, IDC_LIST2, m_CacheEntriesList);
 	DDX_Control(pDX, IDC_MouseHelpCaption, m_MouseHelp);
+	DDX_Control(pDX, IDC_PROGRESS, m_StatusDisplay);
 	DDX_Control(pDX, IDC_BuildProjects, m_Configure);
 	DDX_CBStringExact(pDX, IDC_Generator, m_GeneratorChoiceString);
 	DDX_Check(pDX, IDC_AdvancedValues, m_AdvancedValues);
@@ -288,10 +287,10 @@ BOOL CMakeSetupDialog::OnInitDialog()
     
   // Set the version number
   char tmp[1024];
-  sprintf(tmp,"Version %d.%d - %s", cmake::GetMajorVersion(),
+  sprintf(tmp,"CMake %d.%d - %s", cmake::GetMajorVersion(),
           cmake::GetMinorVersion(), cmake::GetReleaseVersion());
-  SetDlgItemText(IDC_CMAKE_VERSION, tmp);
   SetDlgItemText(IDC_PROGRESS, "");
+  this->SetWindowText(tmp);
   this->UpdateData(FALSE);
   return TRUE;  // return TRUE  unless you set the focus to a control
 }
@@ -987,13 +986,6 @@ void CMakeSetupDialog::OnSize(UINT nType, int cx, int cy)
     deltax = int(deltax + m_deltaXRemainder);
     m_deltaXRemainder = float(deltax%2);
 
-    m_VersionDisplay.GetWindowRect(&cRect);
-    this->ScreenToClient(&cRect);
-    m_VersionDisplay.SetWindowPos(&wndBottom, cRect.left, cRect.top + deltay, 
-                                  cRect.Width() + deltax/2,  cRect.Height(),
-                                  SWP_NOCOPYBITS);
-
-   
 
     m_Configure.GetWindowRect(&cRect);
     this->ScreenToClient(&cRect);