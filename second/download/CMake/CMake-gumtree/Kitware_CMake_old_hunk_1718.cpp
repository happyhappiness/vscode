  int cfileoutputcount = 0;

  char cfileoutputname[100];

  sprintf(cfileoutputname, "CoverageLog-%d.xml", cfileoutputcount++);

  if (!this->OpenOutputFile("", cfileoutputname, cfileoutput))

    {

    std::cout << "Cannot open log file" << std::endl;

    return 1;

