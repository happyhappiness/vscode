            fprintf(stderr,"   Passed\n");
            if (output != "")
              {
              std::cout << "Before dart check" << std::endl;
              if (dartStuff.find(output.c_str()))
                {
                std::string res = dartStuff.match(1);
                cmSystemTools::ReplaceString(output, res.c_str(),"");
                cres.m_RegressionImages = this->GenerateRegressionImages(res);
                }
              if (output != "" && m_Verbose)
                {
