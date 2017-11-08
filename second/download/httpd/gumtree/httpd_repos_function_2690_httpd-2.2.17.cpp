void _NonAppStop( void )
{
  if (getenv("_IN_NETWARE_BASH_") == NULL) {
    uint16_t row, col;

    GetScreenSize(&row, &col);
    gotorowcol(row-1, 0);
    printf("<Press any key to close screen> ");
    getcharacter();
  }
}