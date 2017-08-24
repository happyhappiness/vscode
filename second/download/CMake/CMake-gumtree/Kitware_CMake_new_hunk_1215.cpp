      {
      percent = 99;
      }
    cmCTestLog(this->CTest, HANDLER_OUTPUT, std::endl
      << static_cast<int>(percent + .5) << "% tests passed, "
      << failed.size() << " tests failed out of " << total << std::endl);
    //fprintf(stderr,"\n%.0f%% tests passed, %i tests failed out of %i\n",
