void bindexplib::WriteFile(FILE* file)
{
  fprintf(file,"EXPORTS \n");
  for(std::set<std::string>::const_iterator i = this->DataSymbols.begin();
      i!= this->DataSymbols.end(); ++i)
    {
    fprintf(file, "\t%s \t DATA\n", i->c_str());
    }
  for(std::set<std::string>::const_iterator i = this->Symbols.begin();
      i!= this->Symbols.end(); ++i)
    {
    fprintf(file, "\t%s\n", i->c_str());
    }
}