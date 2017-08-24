{
    YY_BUFFER_STATE current = cmFortranLexer_GetCurrentBuffer(parser->Scanner);
    std::string dir = cmSystemTools::GetParentDirectory(fname);
    cmFortranFile f(file, current, dir);
    YY_BUFFER_STATE buffer =
      cmFortran_yy_create_buffer(CM_NULLPTR, 16384, parser->Scanner);
    cmFortran_yy_switch_to_buffer(buffer, parser->Scanner);
    parser->FileStack.push(f);
    return true;
  }