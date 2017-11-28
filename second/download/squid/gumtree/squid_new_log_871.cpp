printf("Received from %s [%s]\n",
               ipa.toStr(tmp,MAX_HOSTNAMELEN),
               (hp && hp->h_name) ? hp->h_name : "Unknown");