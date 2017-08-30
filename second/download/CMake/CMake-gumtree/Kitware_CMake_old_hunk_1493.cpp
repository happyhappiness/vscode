                 "                    (ClientData *)NULL, NULL);\n\n");

    }

  

  for (i = 0; i < m_Commands.size(); i++)

    {

    fprintf(fout,"  %s_Init(interp);\n", capcommands[i].c_str());

    }

