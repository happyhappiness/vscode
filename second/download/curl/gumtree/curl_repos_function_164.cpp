static void suboption(struct UrlData *data)
{
   printsub(data, '<', (unsigned char *)subbuffer, SB_LEN()+2);
   return;
}