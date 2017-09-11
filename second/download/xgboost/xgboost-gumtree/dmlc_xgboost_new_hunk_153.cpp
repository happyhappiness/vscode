      } else {
        if (!all_links[i].sock.IsClosed()) all_links[i].sock.Close();
      }
    }
    int ngood = static_cast<int>(good_link.size());
    Assert(tracker.SendAll(&ngood, sizeof(ngood)) == sizeof(ngood),
           "ReConnectLink failure 5");
