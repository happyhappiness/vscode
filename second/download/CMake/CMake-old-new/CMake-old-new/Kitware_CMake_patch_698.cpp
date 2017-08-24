@@ -117,13 +117,41 @@ void updateProgress(const char *msg, float prog, void *cd)
     sprintf(tmp,"%s",msg);    
     }
   CMakeSetupDialog *self = (CMakeSetupDialog *)cd;
-  self->SetDlgItemText(IDC_PROGRESS, tmp);
+  self->SetDlgItemText(IDC_PROGRESS, tmp); 
+  CWnd* cancel = self->GetDlgItem(IDCANCEL);
+  //
+  // Retrieve and dispatch any waiting messages.
+  //
+  MSG wmsg;
+  while (::PeekMessage (&wmsg, NULL, 0, 0, PM_REMOVE))
+    {
+    switch(wmsg.message)
+      {
+      case WM_LBUTTONDOWN:
+      case WM_LBUTTONUP:
+      case WM_LBUTTONDBLCLK:
+      {
+      if(wmsg.hwnd == cancel->m_hWnd)
+        {
+        ::DispatchMessage(&wmsg);
+        }
+      }
+      break;
+      case WM_COMMAND:
+      case WM_SETCURSOR:
+      case WM_PAINT:
+        ::DispatchMessage(&wmsg);
+      break;
+      }
+    }
 }
 
 CMakeSetupDialog::CMakeSetupDialog(const CMakeCommandLineInfo& cmdInfo,
                                    CWnd* pParent /*=NULL*/)
   : CDialog(CMakeSetupDialog::IDD, pParent)
-{
+{ 
+  m_Cursor = LoadCursor(NULL, IDC_ARROW);
+  m_RunningConfigure = false;
   cmSystemTools::SetRunCommandHideConsole(true);
   cmSystemTools::SetErrorCallback(MFCMessageCallback);
   m_RegistryKey  = "Software\\Kitware\\CMakeSetup\\Settings\\StartPath";
@@ -208,7 +236,6 @@ BEGIN_MESSAGE_MAP(CMakeSetupDialog, CDialog)
   ON_WM_SYSCOMMAND()
   ON_WM_PAINT()
   ON_WM_QUERYDRAGICON()
-  ON_WM_DROPFILES()
   ON_BN_CLICKED(IDC_BUTTON2, OnBrowseWhereSource)
   ON_BN_CLICKED(IDC_BuildProjects, OnConfigure)
   ON_BN_CLICKED(IDC_BUTTON3, OnBrowseWhereBuild)
@@ -221,10 +248,12 @@ BEGIN_MESSAGE_MAP(CMakeSetupDialog, CDialog)
   ON_BN_CLICKED(IDC_OK, OnOk)
   ON_CBN_EDITCHANGE(IDC_Generator, OnEditchangeGenerator)
   ON_BN_CLICKED(IDC_HELP_BUTTON, OnHelpButton)
-  ON_BN_CLICKED(IDCANCEL, OnCancel)
   ON_BN_CLICKED(IDC_AdvancedValues, OnAdvancedValues)
   ON_BN_DOUBLECLICKED(IDC_AdvancedValues, OnDoubleclickedAdvancedValues)
-  //}}AFX_MSG_MAP
+  ON_WM_DROPFILES()
+  ON_BN_CLICKED(IDCANCEL, OnCancel)
+	ON_WM_SETCURSOR()
+	//}}AFX_MSG_MAP
 END_MESSAGE_MAP()
 
 /////////////////////////////////////////////////////////////////////////////
@@ -606,8 +635,10 @@ void CMakeSetupDialog::RunCMake(bool generateProjectFiles)
       }
     }
   // set the wait cursor
-  ::SetCursor(LoadCursor(NULL, IDC_WAIT));  
-
+  m_Cursor = LoadCursor(NULL, IDC_WAIT);
+  ::SetCursor(m_Cursor);
+  m_RunningConfigure = true;
+  
   // get all the info from the dialog
   this->UpdateData();
   // always save the current gui values to disk
@@ -649,8 +680,10 @@ void CMakeSetupDialog::RunCMake(bool generateProjectFiles)
   this->SaveToRegistry();
   // path is up-to-date now
   m_BuildPathChanged = false;
-  // put the cursor back
-  ::SetCursor(LoadCursor(NULL, IDC_ARROW));
+  // put the cursor back 
+  m_Cursor = LoadCursor(NULL, IDC_ARROW);
+  ::SetCursor(m_Cursor);
+  m_RunningConfigure = false;
   cmSystemTools::ResetErrorOccuredFlag();
 }
 
@@ -1054,6 +1087,17 @@ void CMakeSetupDialog::OnGetMinMaxInfo( MINMAXINFO FAR* lpMMI )
 
 void CMakeSetupDialog::OnCancel()
 {
+  if(m_RunningConfigure)
+    {
+     if(MessageBox("You are in the middle of a Configure.\n"
+                   "If you Cancel now the configure information will be lost.\n"
+                   "Are you sure you want to Cancel?", "Confirm Exit",
+                   MB_YESNO) == IDYES)
+       {
+       cmSystemTools::SetFatalErrorOccured();
+       }
+     return;
+    }
   if(m_CacheEntriesList.IsDirty())
     {
     if(MessageBox("You have changed options but not rebuilt, "
@@ -1395,3 +1439,9 @@ void CMakeSetupDialog::OnDropFiles(HDROP hDropInfo)
 
   DragFinish(hDropInfo);
 }
+
+BOOL CMakeSetupDialog::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
+{
+   ::SetCursor(m_Cursor);
+   return true;
+}