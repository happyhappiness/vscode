    "#include <stdio.h>\n"

    "#include <string.h>\n"

    "#include <stdlib.h>\n";

  if(extraInclude.size())

    {

    fout << "#include \"" << extraInclude << "\"\n";

    }

  

  fout <<

    "\n"

    "// Forward declare test functions\n"

    "\n";



  std::vector<std::string>::iterator testsBegin = i;

