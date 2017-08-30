      percent = 99;
      }
    fprintf(stderr,"\n%.0f%% tests passed, %i tests failed out of %i\n",
      percent, int(failed.size()), total);

    if (failed.size()) 
      {
      std::cerr << "\nThe following tests FAILED:\n";
      for(cmCTest::tm_VectorOfStrings::iterator j = failed.begin();
        j != failed.end(); ++j)
        {   
        std::cerr << "\t" << *j << "\n";
        }
