{
    /* Send the AUTH command */
    result = Curl_pp_sendf(&smtpc->pp, "AUTH %s", mech);
  }