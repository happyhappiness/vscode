
        if ( !m_ShowOnly )
          {
          if (!res || retVal != 0)
            {
            fprintf(stderr,"***Failed\n");
            if (output != "")
              {
              if (dartStuff.find(output.c_str()))
                {
                std::string dartString = dartStuff.match(1);
                cmSystemTools::ReplaceString(output, dartString.c_str(),"");
                cres.m_RegressionImages = this->GenerateRegressionImages(dartString);
                }
              if (output != "" && m_Verbose)
                {
                std::cerr << output.c_str() << "\n";
                }
              }
            failed.push_back(args[0].Value); 
            }
          else
            {
            fprintf(stderr,"   Passed\n");
            if (output != "")
              {
              if (dartStuff.find(output.c_str()))
                {
                std::string dartString = dartStuff.match(1);
                cmSystemTools::ReplaceString(output, dartString.c_str(),"");
                cres.m_RegressionImages = this->GenerateRegressionImages(dartString);
                }
              if (output != "" && m_Verbose)
                {
                std::cerr << output.c_str() << "\n";
                }
              }
            passed.push_back(args[0].Value); 
            }
          }
        cres.m_Output = output;
