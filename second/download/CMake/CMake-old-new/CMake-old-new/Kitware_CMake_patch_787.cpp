@@ -100,10 +100,10 @@ BEGIN_MESSAGE_MAP(CMakeSetupDialog, CDialog)
   ON_WM_PAINT()
   ON_WM_QUERYDRAGICON()
   ON_BN_CLICKED(IDC_BuildProjects, OnBuildProjects)
-  ON_CBN_EDITCHANGE(IDC_WhereBuild, OnChangeWhereBuild)
   ON_BN_CLICKED(IDC_BUTTON2, OnBrowseWhereSource)
   ON_BN_CLICKED(IDC_BUTTON3, OnBrowseWhereBuild)
-  ON_CBN_SELENDOK(IDC_WhereBuild, OnSelendokWhereBuild)
+  ON_CBN_EDITCHANGE(IDC_WhereBuild, OnChangeWhereBuild)
+  ON_CBN_SELCHANGE(IDC_WhereBuild, OnSelendokWhereBuild)
   ON_CBN_SELENDOK(IDC_WhereSource, OnSelendokWhereSource)
   ON_CBN_EDITCHANGE(IDC_WhereSource, OnChangeWhereSource)
 	//}}AFX_MSG_MAP
@@ -147,7 +147,8 @@ BOOL CMakeSetupDialog::OnInitDialog()
   // Set the version number
   char tmp[1024];
   sprintf(tmp,"Version %s", cmMakefile::GetVersion());
-	SetDlgItemText(IDC_CMAKE_VERSION, tmp);
+  SetDlgItemText(IDC_CMAKE_VERSION, tmp);
+  this->UpdateData(FALSE);
   return TRUE;  // return TRUE  unless you set the focus to a control
 }
 
@@ -550,13 +551,12 @@ void CMakeSetupDialog::FillCacheGUIFromCacheManager()
         break;
       }
     }
-  this->UpdateData(FALSE);
 }
 
 // copy from the list box to the cache manager
 void CMakeSetupDialog::FillCacheManagerFromCacheGUI()
 { 
-    cmCacheManager::GetInstance()->GetCacheMap();
+  cmCacheManager::GetInstance()->GetCacheMap();
   std::set<CPropertyItem*> items = m_CacheEntriesList.GetItems();
   for(std::set<CPropertyItem*>::iterator i = items.begin();
       i != items.end(); ++i)