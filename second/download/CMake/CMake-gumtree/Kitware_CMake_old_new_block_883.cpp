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