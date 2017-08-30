        break;
    }
  }
  // Store the result of running the processes.
  if (!results_variable.empty()) {
    switch (cmsysProcess_GetState(cp)) {
      case cmsysProcess_State_Exited: {
        std::vector<std::string> res;
        for (size_t i = 0; i < cmds.size(); ++i) {
          switch (cmsysProcess_GetStateByIndex(cp, static_cast<int>(i))) {
            case kwsysProcess_StateByIndex_Exited: {
              int exitCode =
                cmsysProcess_GetExitValueByIndex(cp, static_cast<int>(i));
              char buf[16];
              sprintf(buf, "%d", exitCode);
              res.push_back(buf);
            } break;
            case kwsysProcess_StateByIndex_Exception:
              res.push_back(cmsysProcess_GetExceptionStringByIndex(
                cp, static_cast<int>(i)));
              break;
            case kwsysProcess_StateByIndex_Error:
            default:
              res.push_back("Error getting the child return code");
              break;
          }
        }
        this->Makefile->AddDefinition(results_variable,
                                      cmJoin(res, ";").c_str());
      } break;
      case cmsysProcess_State_Exception:
        this->Makefile->AddDefinition(results_variable,
                                      cmsysProcess_GetExceptionString(cp));
        break;
      case cmsysProcess_State_Error:
        this->Makefile->AddDefinition(results_variable,
                                      cmsysProcess_GetErrorString(cp));
        break;
      case cmsysProcess_State_Expired:
        this->Makefile->AddDefinition(results_variable,
                                      "Process terminated due to timeout");
        break;
    }
  }

  // Delete the process instance.
  cmsysProcess_Delete(cp);