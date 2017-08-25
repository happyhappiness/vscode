(testCommand == "")
        {
        std::cerr << "Unable to find executable: " <<
          args[1].Value.c_str() << "\n";
        m_TestResults.push_back( cres ); 
        failed.push_back(args[0].Value);
        continue;
        }