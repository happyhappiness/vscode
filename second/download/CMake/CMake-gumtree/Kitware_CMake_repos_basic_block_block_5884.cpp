f((check->localport != needle->localport) ||
           (check->localportrange != needle->localportrange) ||
           (needle->localdev &&
            (!check->localdev || strcmp(check->localdev, needle->localdev))))
          continue;