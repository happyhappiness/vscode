      return -1;

      }



    const char* def = this->Makefile->GetDefinition("CMAKE_MODULE_PATH");

    fprintf(fout, "cmake_minimum_required(VERSION %u.%u.%u.%u)\n",

            cmVersion::GetMajorVersion(), cmVersion::GetMinorVersion(),

