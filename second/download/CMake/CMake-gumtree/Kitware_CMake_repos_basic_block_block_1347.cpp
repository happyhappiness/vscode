(optionId) {
    case kwsysProcess_Option_Detach:
      cp->OptionDetach = value;
      break;
    case kwsysProcess_Option_HideWindow:
      cp->HideWindow = value;
      break;
    case kwsysProcess_Option_MergeOutput:
      cp->MergeOutput = value;
      break;
    case kwsysProcess_Option_Verbatim:
      cp->Verbatim = value;
      break;
    case kwsysProcess_Option_CreateProcessGroup:
      cp->CreateProcessGroup = value;
      break;
    default:
      break;
  }