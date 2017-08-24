(remove(filename) < 0) {
      cmFailed("Unable to remove file. It does not imply that this test "
               "failed, but it *will* be corrupted thereafter if this file is "
               "not removed: ",
               filename);
    } else {
      cmPassed("Find and remove file: ", filename);
    }