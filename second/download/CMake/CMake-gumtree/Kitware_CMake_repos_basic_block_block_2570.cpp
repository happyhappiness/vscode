{
  std::ofstream fout("commandoutput.h");
  if (!fout)
    return 1;
  fout << "#define COMMANDOUTPUT_DEFINE\n";
  fout.close();
  return object();
}