    sprintf(tmp,"%s",msg);    

    }

  CMakeSetupDialog *self = (CMakeSetupDialog *)cd;

  self->SetDlgItemText(IDC_PROGRESS, tmp);

}



CMakeSetupDialog::CMakeSetupDialog(const CMakeCommandLineInfo& cmdInfo,

                                   CWnd* pParent /*=NULL*/)

  : CDialog(CMakeSetupDialog::IDD, pParent)

{

  cmSystemTools::SetRunCommandHideConsole(true);

  cmSystemTools::SetErrorCallback(MFCMessageCallback);

  m_RegistryKey  = "Software\\Kitware\\CMakeSetup\\Settings\\StartPath";

