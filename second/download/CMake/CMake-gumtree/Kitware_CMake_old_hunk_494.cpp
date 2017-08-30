  fprintf(stderr, "\n");
}

//----------------------------------------------------------------------------
void cmComputeLinkDepends::CheckWrongConfigItem(cmLinkItem const& item)
{
  if(!this->OldLinkDirMode)