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





