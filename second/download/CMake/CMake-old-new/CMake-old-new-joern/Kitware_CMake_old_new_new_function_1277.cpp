bool cmCTestSubmitHandler::SubmitUsingHTTP(const cmStdString& localprefix, 
  const std::set<cmStdString>& files,
  const cmStdString& remoteprefix, 
  const cmStdString& url)
{
  CURL *curl;
  CURLcode res;
  FILE* ftpfile;
  char error_buffer[1024];

  /* In windows, this will init the winsock stuff */
  ::curl_global_init(CURL_GLOBAL_ALL);

  cmStdString::size_type kk;
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

      /* enable uploading */
      curl_easy_setopt(curl, CURLOPT_UPLOAD, 1) ;

      /* HTTP PUT please */
      ::curl_easy_setopt(curl, CURLOPT_PUT, 1);
      ::curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);

      cmStdString local_file = localprefix + "/" + *file;
      cmStdString remote_file = remoteprefix + *file;

      *m_LogFile << "\tUpload file: " << local_file.c_str() << " to "
          << remote_file.c_str() << std::endl;

      cmStdString ofile = "";
      for ( kk = 0; kk < remote_file.size(); kk ++ )
        {
        char c = remote_file[kk];
        char hexCh[4] = { 0, 0, 0, 0 };
        hexCh[0] = c;
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
          sprintf(hexCh, "%%%02X", (int)c);
          ofile.append(hexCh);
          break;
        default: 
          ofile.append(hexCh);
          }
        }
      cmStdString upload_as 
        = url + ((url.find("?",0) == cmStdString::npos) ? "?" : "&") 
        + "FileName=" + ofile;

      struct stat st;
      if ( ::stat(local_file.c_str(), &st) )
        {
        cmCTestLog(m_CTest, ERROR_MESSAGE, "   Cannot find file: " << local_file.c_str() << std::endl);
        ::curl_easy_cleanup(curl);
        ::curl_global_cleanup(); 
        return false;
        }

      ftpfile = ::fopen(local_file.c_str(), "rb");
      cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "   Upload file: " << local_file.c_str() << " to " 
        << upload_as.c_str() << " Size: " << st.st_size << std::endl);


      // specify target
      ::curl_easy_setopt(curl,CURLOPT_URL, upload_as.c_str());

      // now specify which file to upload
      ::curl_easy_setopt(curl, CURLOPT_INFILE, ftpfile);

      // and give the size of the upload (optional)
      ::curl_easy_setopt(curl, CURLOPT_INFILESIZE, static_cast<long>(st.st_size));

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

      // Now run off and do what you've been told!
      res = ::curl_easy_perform(curl);

      cmCTestLog(m_CTest, DEBUG, "CURL output: ["
        << cmCTestLogWrite(&*chunk.begin(), chunk.size()) << "]" << std::endl);
      cmCTestLog(m_CTest, DEBUG, "CURL debug output: ["
        << cmCTestLogWrite(&*chunkDebug.begin(), chunkDebug.size()) << "]" << std::endl);

      fclose(ftpfile);
      if ( res )
        {
        cmCTestLog(m_CTest, ERROR_MESSAGE, "   Error when uploading file: " << local_file.c_str() << std::endl);
        cmCTestLog(m_CTest, ERROR_MESSAGE, "   Error message was: " << error_buffer << std::endl);
        *m_LogFile << "   Error when uploading file: " << local_file.c_str() << std::endl
          << "   Error message was: " << error_buffer << std::endl
          << "   Curl output was: " << cmCTestLogWrite(&*chunk.begin(), chunk.size()) << std::endl;
        cmCTestLog(m_CTest, ERROR_MESSAGE, "CURL output: ["
          << cmCTestLogWrite(&*chunk.begin(), chunk.size()) << "]" << std::endl);
        ::curl_easy_cleanup(curl);
        ::curl_global_cleanup(); 
        return false;
        }
      // always cleanup
      ::curl_easy_cleanup(curl);
      cmCTestLog(m_CTest, HANDLER_OUTPUT, "   Uploaded: " + local_file << std::endl);
      }
    }
  ::curl_global_cleanup(); 
  return true;
}