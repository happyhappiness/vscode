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

      std::string turl = url + "?xmlfile=" + ofile;

      if ( m_Verbose )

        {

        std::cout << "  Trigger url: " << turl.c_str() << std::endl;

        }

      curl_easy_setopt(curl, CURLOPT_URL, turl.c_str());

      if ( curl_easy_perform(curl) )

        {

        std::cout << "  Error when triggering: " << turl.c_str() << std::endl;

        ::curl_easy_cleanup(curl);

        ::curl_global_cleanup(); 

        return false;

