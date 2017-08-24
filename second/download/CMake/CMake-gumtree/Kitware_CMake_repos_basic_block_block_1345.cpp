{
    case kwsysProcess_Option_Detach:
      return cp->OptionDetach;
    case kwsysProcess_Option_HideWindow:
      return cp->HideWindow;
    case kwsysProcess_Option_MergeOutput:
      return cp->MergeOutput;
    case kwsysProcess_Option_Verbatim:
      return cp->Verbatim;
    case kwsysProcess_Option_CreateProcessGroup:
      return cp->CreateProcessGroup;
    default:
      return 0;
  }