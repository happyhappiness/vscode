bool cmCTestSubmitHandler::TriggerUsingHTTP(const std::set<cmStdString>& files,
  const cmStdString& remoteprefix, 
  const cmStdString& url)
{
  CURL *curl;
  char error_buffer[1024];

  /* In windows, this will init the winsock stuff */
  ::curl_global_init(CURL_GLOBAL_ALL);

  cmCTest::tm_SetOfStrings::const_iterator file;
  for ( file = files.begin(); file != files.end(); ++file )
    {
    /* get a curl handle */
    curl = curl_easy_init();
    if(curl) 
      {
      // Using proxy
      if ( m_HTTPProxyType > 0 )
        {
        curl_easy_setopt(curl, CURLOPT_PROXY, m_HTTPProxy.c_str()); 
        switch (m_HTTPProxyType)
          {
        case 2:
          curl_easy_setopt(curl, CURLOPT_PROXYTYPE, CURLPROXY_SOCKS4);
          break;
        case 3:
          curl_easy_setopt(curl, CURLOPT_PROXYTYPE, CURLPROXY_SOCKS5);
          break;
        default:
          curl_easy_setopt(curl, CURLOPT_PROXYTYPE, CURLPROXY_HTTP);           
          if (m_HTTPProxyAuth.size() > 0)
            {
            curl_easy_setopt(curl, CURLOPT_PROXYUSERPWD,
              m_HTTPProxyAuth.c_str());
            }
          }
        }

      ::curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);

      // and give curl the buffer for errors
      ::curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, &error_buffer);

      // specify handler for output
      ::curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, cmCTestSubmitHandlerWriteMemoryCallback);
      ::curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, cmCTestSubmitHandlerCurlDebugCallback);

      /* we pass our 'chunk' struct to the callback function */
      cmCTestSubmitHandlerVectorOfChar chunk;
      cmCTestSubmitHandlerVectorOfChar chunkDebug;
      ::curl_easy_setopt(curl, CURLOPT_FILE, (void *)&chunk);
      ::curl_easy_setopt(curl, CURLOPT_DEBUGDATA, (void *)&chunkDebug);

      cmStdString rfile = remoteprefix + *file;
      cmStdString ofile = "";
      cmStdString::iterator kk;
      for ( kk = rfile.begin(); kk < rfile.end(); ++ kk)
        {
        char c = *kk;
        char hex[4] = { 0, 0, 0, 0 };
        hex[0] = c;
        switch ( c )
          {
        case '+':
        case '?':
        case '/':
        case '\\':
        case '&':
        case ' ':
        case '=':
        case '%':
          sprintf(hex, "%%%02X", (int)c);
          ofile.append(hex);
          break;
        default: 
          ofile.append(hex);
          }
        }
      cmStdString turl 
        = url + ((url.find("?",0) == cmStdString::npos) ? "?" : "&") 
        + "xmlfile=" + ofile;
      *m_LogFile << "Trigger url: " << turl.c_str() << std::endl;
      cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "   Trigger url: " << turl.c_str() << std::endl);
      curl_easy_setopt(curl, CURLOPT_URL, turl.c_str());
      if ( curl_easy_perform(curl) )
        {
        cmCTestLog(m_CTest, ERROR_MESSAGE, "   Error when triggering: " << turl.c_str() << std::endl);
        cmCTestLog(m_CTest, ERROR_MESSAGE, "   Error message was: " << error_buffer << std::endl);
        *m_LogFile << "\tTrigerring failed with error: " << error_buffer << std::endl
          << "   Error message was: " << error_buffer << std::endl
          << "   Curl output was: " << cmCTestLogWrite(&*chunk.begin(), chunk.size()) << std::endl;
        cmCTestLog(m_CTest, ERROR_MESSAGE, "CURL output: ["
          << cmCTestLogWrite(&*chunk.begin(), chunk.size()) << "]" << std::endl);
        ::curl_easy_cleanup(curl);
        ::curl_global_cleanup(); 
        return false;
        }

      cmCTestLog(m_CTest, DEBUG, "CURL output: ["
        << cmCTestLogWrite(&*chunk.begin(), chunk.size()) << "]" << std::endl);
      cmCTestLog(m_CTest, DEBUG, "CURL debug output: ["
        << cmCTestLogWrite(&*chunkDebug.begin(), chunkDebug.size()) << "]" << std::endl);

      // always cleanup
      ::curl_easy_cleanup(curl);
      cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, std::endl);
      }
    }
  ::curl_global_cleanup(); 
  cmCTestLog(m_CTest, HANDLER_OUTPUT, "   Dart server triggered..." << std::endl);
  return true;
}