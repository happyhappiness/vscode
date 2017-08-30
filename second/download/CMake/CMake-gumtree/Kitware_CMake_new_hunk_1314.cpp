    strftime(current_time, 1000, "%a %b %d %H:%M:%S %Z %Y", t);

    }

  cmCTestLog(this, DEBUG, "   Current_Time: " << current_time << std::endl);

  return cmXMLSafe(cmCTest::CleanString(current_time)).str();

}



//----------------------------------------------------------------------

