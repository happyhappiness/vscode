static int ftp_pl_get_permission(const char *str)
{
  int permissions = 0;
  /* USER */
  if(str[0] == 'r')
    permissions |= 1 << 8;
  else if(str[0] != '-')
    permissions |= FTP_LP_MALFORMATED_PERM;
  if(str[1] == 'w')
    permissions |= 1 << 7;
  else if(str[1] != '-')
    permissions |= FTP_LP_MALFORMATED_PERM;

  if(str[2] == 'x')
    permissions |= 1 << 6;
  else if(str[2] == 's') {
    permissions |= 1 << 6;
    permissions |= 1 << 11;
  }
  else if(str[2] == 'S')
    permissions |= 1 << 11;
  else if(str[2] != '-')
    permissions |= FTP_LP_MALFORMATED_PERM;
  /* GROUP */
  if(str[3] == 'r')
    permissions |= 1 << 5;
  else if(str[3] != '-')
    permissions |= FTP_LP_MALFORMATED_PERM;
  if(str[4] == 'w')
    permissions |= 1 << 4;
  else if(str[4] != '-')
    permissions |= FTP_LP_MALFORMATED_PERM;
  if(str[5] == 'x')
    permissions |= 1 << 3;
  else if(str[5] == 's') {
    permissions |= 1 << 3;
    permissions |= 1 << 10;
  }
  else if(str[5] == 'S')
    permissions |= 1 << 10;
  else if(str[5] != '-')
    permissions |= FTP_LP_MALFORMATED_PERM;
  /* others */
  if(str[6] == 'r')
    permissions |= 1 << 2;
  else if(str[6] != '-')
    permissions |= FTP_LP_MALFORMATED_PERM;
  if(str[7] == 'w')
    permissions |= 1 << 1;
  else if(str[7] != '-')
      permissions |= FTP_LP_MALFORMATED_PERM;
  if(str[8] == 'x')
    permissions |= 1;
  else if(str[8] == 't') {
    permissions |= 1;
    permissions |= 1 << 9;
  }
  else if(str[8] == 'T')
    permissions |= 1 << 9;
  else if(str[8] != '-')
    permissions |= FTP_LP_MALFORMATED_PERM;

  return permissions;
}