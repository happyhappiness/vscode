void CMakeSetupFrm::DoInitFrame(cmCommandLineInfo &cm, const wxString &fn)
{ 
    // path to where cmake.exe is
    // m_PathToExecutable = cm.GetPathToExecutable().c_str();
    m_PathToExecutable = fn;

    // adjust size of last bar, to display % progress
    wxStatusBar *bar = GetStatusBar();
    if(bar)
    {
        wxASSERT(bar->GetFieldsCount() > 1);
        
        // fill all with -1. Why this way? because the count of the status bars
        // can change. All of the widths must be accounted for and initialised
        int *widths = new int[bar->GetFieldsCount()];
        for(int i = 0; i < bar->GetFieldsCount(); i++)
            widths[i] = -1;

        // the % field
        widths[1] = 75;
        bar->SetStatusWidths(bar->GetFieldsCount(), widths);
        delete widths;
    }

    wxString name, generator;
    std::vector<std::string> names;
  
    m_RunningConfigure = false;

    // set grid labels
    m_cmOptions->SetColLabelValue(0, wxT("Cache Name"));
    m_cmOptions->SetColLabelValue(1, wxT("Cache Value"));
    m_cmOptions->SetProjectGenerated(false);

    // set drop target
    m_cmOptions->SetDropTarget(new DnDFile(m_cmBuildPath));

    m_cmake->GetRegisteredGenerators(names);
    for(std::vector<std::string>::iterator i = names.begin(); i != names.end(); ++i)
    {
        name = i->c_str();
        m_cmGeneratorChoice->Append(name);
    }
    
    // sync advanced option with grid
    m_cmOptions->SetShowAdvanced(m_cmShowAdvanced->GetValue());

    // if we have a command line query that a generator 
    // needs to be chosen instead of the default, take it
    bool foundGivenGenerator = false;
    if(!cm.m_GeneratorChoiceString.IsEmpty())
    {
        // set proper discovered generator
        foundGivenGenerator = m_cmGeneratorChoice->SetStringSelection(cm.m_GeneratorChoiceString);  
    }

    // if none selected, we will see if VS8, VS7 or VS6 is present
    if(!foundGivenGenerator || m_cmGeneratorChoice->GetValue().IsEmpty())
    {
        std::string mp;
        mp = "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\VisualStudio\\8.0\\Setup;Dbghelp_path]";
        cmSystemTools::ExpandRegistryValues(mp);
        if(mp != "/registry")
            generator = wxT("Visual Studio 8 2005");
        else
        {
            mp = "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\VisualStudio\\7.1;InstallDir]";
            cmSystemTools::ExpandRegistryValues(mp);
            if (mp != "/registry")
                generator = wxT("Visual Studio 7 .NET 2003");
            else
            {
                mp = "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\VisualStudio\\7.0;InstallDir]";
                cmSystemTools::ExpandRegistryValues(mp);
                if (mp != "/registry")
                    generator = wxT("Visual Studio 7");
                else
                    generator = wxT("Visual Studio 6");         
            }
        }
    }

    // set proper discovered generator
    m_cmGeneratorChoice->SetStringSelection(generator);
    
    wxString str;
    str.Printf("CMake %d.%d - %s", cmVersion::GetMajorVersion(),
               cmVersion::GetMinorVersion(), 
               cmVersion::GetReleaseVersion().c_str());
    str.Printf("CMakeSetup v%i.%i%s", CMAKEGUI_MAJORVER, CMAKEGUI_MINORVER, CMAKEGUI_ADDVER);

    SetTitle(str);
    wxString path;
    
    // get last 5 used projects
    for(size_t i = 0; i < CM_MAX_RECENT_PATHS; i++)
    {
        path.Printf("%s%i", _(CM_RECENT_BUILD_PATH), i);
        if(m_config->Read(path, &str))
            AppendPathToRecentList(str);
    }

    // get query items
    for(size_t i = 0; i < CM_MAX_SEARCH_QUERIES; i++)
    {
        path.Printf("%s%i", _(CM_SEARCH_QUERY), i);
        if(m_config->Read(path, &str))
            m_cmSearchQuery->Append(str);
    }


    // make sure the call to update grid is not executed
    m_noRefresh = true;
    m_cmSearchQuery->SetValue(_(""));
    m_noRefresh = false;

    // Get the parameters from the command line info
    // If an unknown parameter is found, try to interpret it too, since it
    // is likely to be a file dropped on the shortcut :)
    bool sourceDirLoaded = false,
         buildDirLoaded = false;
    
    if(cm.m_LastUnknownParameter.empty())
    {
        if(cm.m_WhereSource.size() > 0 )
        {
            m_cmProjectPath->SetValue(cm.m_WhereSource.c_str());
            sourceDirLoaded = true;
        }   
    
        if (cm.m_WhereBuild.size() > 0 )
        {
            m_cmBuildPath->SetValue(cm.m_WhereBuild.c_str());
            buildDirLoaded = true;
        }
            
        m_cmShowAdvanced->SetValue(cm.m_AdvancedValues);
    }
    else
    {
        m_cmShowAdvanced->SetValue(false);
        
        // TODO: Interpret directory from dropped shortcut
        //this->ChangeDirectoriesFromFile(cmdInfo->m_LastUnknownParameter.c_str());
    }

    if (cm.m_ExitAfterLoad)
    {
        int id = GetId();
        m_ExitTimer = new wxTimer(this, id);
        m_ExitTimer->Start(3000);

        Connect( id, wxEVT_TIMER,(wxObjectEventFunction) &CMakeSetupFrm::OnExitTimer ); 

    } 

    // retrieve settings, this needs to be done here
    // because writing to the m_cmBuildPath triggers a cache reload
    if(!sourceDirLoaded && m_config->Read(CM_LASTPROJECT_PATH, &str))
        m_cmProjectPath->SetValue(str);

    if(!buildDirLoaded)
    {
        m_cmOptions->RemoveAll();
        if(m_config->Read(CM_LASTBUILD_PATH, &str))
            m_cmBuildPath->SetValue(str);
    }

    // set window size from settings
    long xsize, ysize, splitpos;
    if(m_config->Read(CM_XSIZE, &xsize) && m_config->Read(CM_YSIZE, &ysize) &&
       m_config->Read(CM_SPLITTERPOS, &splitpos))
    {
        SetSize(xsize, ysize);
        m_splitter->SetSashPosition(splitpos);
    }

    if(m_config->Read(CM_XPOS, &xsize) && m_config->Read(CM_YPOS, &ysize))
        SetSize(xsize, ysize, -1, -1, wxSIZE_USE_EXISTING);

    UpdateWindowState();
}