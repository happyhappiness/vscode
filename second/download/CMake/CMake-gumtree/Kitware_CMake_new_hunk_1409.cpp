      // is this test in the list of tests to run? If not then skip it

      if ((this->TestsToRun.size() &&

           std::find(this->TestsToRun.begin(),

                     this->TestsToRun.end(), inREcnt)

           == this->TestsToRun.end()) || !it->IsInBasedOnREOptions)

        {

        continue;

        }

      }

    

    // process this one test

    this->ProcessOneTest(&(*it), passed, failed, cnt, tmsize);

    }



  this->EndTest = this->CTest->CurrentTime();

