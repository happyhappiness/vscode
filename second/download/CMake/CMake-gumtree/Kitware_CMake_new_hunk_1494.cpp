    {
    return false;
    }

  // capitalized commands just once
  std::vector<std::string> capcommands;
  for (i = 0; i < m_Commands.size(); i++)
    {
    capcommands.push_back(cmSystemTools::Capitalized(m_Commands[i]));
    }
  
  fprintf(fout,"#include \"vtkTclUtil.h\"\n");
  
