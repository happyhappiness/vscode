int win32_init(void)
{
  WORD wVersionRequested;  
  WSADATA wsaData; 
  int err; 
  wVersionRequested = MAKEWORD(1, 1); 
    
  err = WSAStartup(wVersionRequested, &wsaData); 
    
  if (err != 0) 
    /* Tell the user that we couldn't find a useable */ 
    /* winsock.dll.     */ 
    return 1;
    
  /* Confirm that the Windows Sockets DLL supports 1.1.*/ 
  /* Note that if the DLL supports versions greater */ 
  /* than 1.1 in addition to 1.1, it will still return */ 
  /* 1.1 in wVersion since that is the version we */ 
  /* requested. */ 
    
  if ( LOBYTE( wsaData.wVersion ) != 1 || 
       HIBYTE( wsaData.wVersion ) != 1 ) { 
    /* Tell the user that we couldn't find a useable */ 

    /* winsock.dll. */ 
    WSACleanup(); 
    return 1; 
  }
  return 0; /* 0 is ok */
}