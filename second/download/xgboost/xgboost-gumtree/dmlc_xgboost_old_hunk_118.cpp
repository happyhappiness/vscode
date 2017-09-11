        utils::Socket::Error("Connect");
      } else {
        fprintf(stderr, "retry connect to ip(retry time %d): [%s]\n", retry, tracker_uri.c_str());
        sleep(1);
        continue;
      }
    }
