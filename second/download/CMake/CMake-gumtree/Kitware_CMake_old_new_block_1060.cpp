{
      char buffer[33];
      sprintf(buffer, "&lt;%d&gt;", (int)ch);
      //sprintf(buffer, "&#x%0x;", (unsigned int)ch);
      result.insert(result.end(), buffer, buffer+strlen(buffer));
      }