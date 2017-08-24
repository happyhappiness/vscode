{
  kwsys::RegularExpression urlRe(VTK_URL_REGEX);
  if (!urlRe.find(URL))
    return false;

  // match 0 URL
  // match 1 protocol
  // match 2 mangled user
  // match 3 username
  // match 4 mangled password
  // match 5 password
  // match 6 hostname
  // match 7 mangled port
  // match 8 dataport
  // match 9 database name

  protocol = urlRe.match(1);
  username = urlRe.match(3);
  password = urlRe.match(5);
  hostname = urlRe.match(6);
  dataport = urlRe.match(8);
  database = urlRe.match(9);

  return true;
}