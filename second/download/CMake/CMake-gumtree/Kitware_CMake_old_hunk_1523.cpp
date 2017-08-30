          sprintf(hexCh, "%%%02X", (int)c);

          ofile.append(hexCh);

          break;

        default: 

          ofile.append(hexCh);

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



      if ( chunk.size() > 0 )

        {

        cmCTestLog(m_CTest, DEBUG, "CURL output: ["

          << cmCTestLogWrite(&*chunk.begin(), chunk.size()) << "]" << std::endl);

        }

      if ( chunkDebug.size() > 0 )

        {

        cmCTestLog(m_CTest, DEBUG, "CURL debug output: ["

          << cmCTestLogWrite(&*chunkDebug.begin(), chunkDebug.size()) << "]" << std::endl);

        }



      // always cleanup

      ::curl_easy_cleanup(curl);

      cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, std::endl);

      }

    }

  ::curl_global_cleanup(); 

  cmCTestLog(m_CTest, HANDLER_OUTPUT, "   Dart server triggered..." << std::endl);

  return true;

}



//----------------------------------------------------------------------------

bool cmCTestSubmitHandler::SubmitUsingSCP(

  const cmStdString& scp_command, 

  const cmStdString& localprefix, 

  const std::set<cmStdString>& files,

  const cmStdString& remoteprefix, 

  const cmStdString& url)

{

  if ( !scp_command.size() || !localprefix.size() ||

