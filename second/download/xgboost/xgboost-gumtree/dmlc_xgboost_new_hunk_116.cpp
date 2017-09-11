        utils::Socket::Error("Connect");
      } else {
        fprintf(stderr, "retry connect to ip(retry time %d): [%s]\n", retry, tracker_uri.c_str());
        #ifdef _MSC_VER
        Sleep(1);
        #else
        sleep(1);
        #endif
        continue;
      }
    }
