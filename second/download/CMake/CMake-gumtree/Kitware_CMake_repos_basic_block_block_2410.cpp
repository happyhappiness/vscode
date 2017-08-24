{
  // match 0 entire url
  // match 1 protocol
  // match 2 dataglom following protocol://
  kwsys::RegularExpression urlRe(VTK_URL_PROTOCOL_REGEX);

  if (!urlRe.find(URL))
    return false;

  protocol = urlRe.match(1);
  dataglom = urlRe.match(2);

  return true;
}