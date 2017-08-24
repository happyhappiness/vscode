
  // capitalized commands just once
  std::vector<std::string> capcommands;
  for (i = 0; i < this->Commands.size(); i++)
    {
    capcommands.push_back(cmSystemTools::Capitalized(this->Commands[i]));
    }
  
  fprintf(fout,"#include \"vtkTclUtil.h\"\n");
