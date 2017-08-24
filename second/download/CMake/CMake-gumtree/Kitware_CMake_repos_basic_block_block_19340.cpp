(backlog == 0)
    backlog = 1;
  else if (backlog < 0)
    backlog = SOMAXCONN