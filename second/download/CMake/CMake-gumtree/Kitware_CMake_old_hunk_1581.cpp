            state, kwsysProcess_GetState(kp));
    result = 1;
    }
  
  kwsysProcess_Delete(kp);
  return result;
