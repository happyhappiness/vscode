DWORD wait_for_many_objects(DWORD nCount, CONST HANDLE *lpHandles, 
                            DWORD dwSeconds)
{
    time_t tStopTime;
    DWORD dwRet = WAIT_TIMEOUT;
    DWORD dwIndex=0;
    BOOL bFirst = TRUE;
  
    tStopTime = time(NULL) + dwSeconds;
  
    do {
        if (!bFirst)
            Sleep(1000);
        else
            bFirst = FALSE;
          
        for (dwIndex = 0; dwIndex * MAXIMUM_WAIT_OBJECTS < nCount; dwIndex++) {
            dwRet = WaitForMultipleObjects( 
                min(MAXIMUM_WAIT_OBJECTS, nCount - (dwIndex * MAXIMUM_WAIT_OBJECTS)),
                lpHandles + (dwIndex * MAXIMUM_WAIT_OBJECTS), 
                0, 0);
                                           
            if (dwRet != WAIT_TIMEOUT) {                                          
              break;
            }
        }
    } while((time(NULL) < tStopTime) && (dwRet == WAIT_TIMEOUT));
    
    return dwRet;
}