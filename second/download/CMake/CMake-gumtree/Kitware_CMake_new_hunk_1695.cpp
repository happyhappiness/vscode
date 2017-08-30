    sprintf(tmp,"%s",msg);    

    }

  CMakeSetupDialog *self = (CMakeSetupDialog *)cd;

  self->SetDlgItemText(IDC_PROGRESS, tmp); 

  CWnd* cancel = self->GetDlgItem(IDCANCEL);

  //

  // Retrieve and dispatch any waiting messages.

  //

  MSG wmsg;

  while (::PeekMessage (&wmsg, NULL, 0, 0, PM_REMOVE))

    {

    switch(wmsg.message)

      {

      case WM_LBUTTONDOWN:

      case WM_LBUTTONUP:

      case WM_LBUTTONDBLCLK:

      {

      if(wmsg.hwnd == cancel->m_hWnd)

        {

        ::DispatchMessage(&wmsg);

        }

      }

      break;

      case WM_COMMAND:

      case WM_SETCURSOR:

      case WM_PAINT:

        ::DispatchMessage(&wmsg);

      break;

      }

    }

}



CMakeSetupDialog::CMakeSetupDialog(const CMakeCommandLineInfo& cmdInfo,

                                   CWnd* pParent /*=NULL*/)

  : CDialog(CMakeSetupDialog::IDD, pParent)

{ 

  m_Cursor = LoadCursor(NULL, IDC_ARROW);

  m_RunningConfigure = false;

  cmSystemTools::SetRunCommandHideConsole(true);

  cmSystemTools::SetErrorCallback(MFCMessageCallback);

  m_RegistryKey  = "Software\\Kitware\\CMakeSetup\\Settings\\StartPath";

