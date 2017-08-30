  std::ofstream cfileoutput; 

  int cfileoutputcount = 0;

  char cfileoutputname[100];

  std::string local_start_time = ::CurrentTime();

  std::string local_end_time;

  for ( cit = coverageresults.begin(); cit != coverageresults.end(); cit ++ )

