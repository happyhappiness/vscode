        if ( ftit->m_Status != cmCTestTestHandler::COMPLETED )
          {
          ofs << ftit->m_TestCount << ":" << ftit->m_Name << std::endl;
          cmCTestLog(m_CTest, HANDLER_OUTPUT, "\t" << std::setw(3)
            << ftit->m_TestCount << " - " << ftit->m_Name.c_str() << " ("
            << this->GetTestStatus(ftit->m_Status) << ")" << std::endl);
          }
        }

