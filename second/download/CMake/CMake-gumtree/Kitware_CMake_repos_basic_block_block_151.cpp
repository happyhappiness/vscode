r(row=0, pBuffer=field->buf; 
      row < height; 
      row++, pBuffer += width )
    {
      if ((len = (int)( After_End_Of_Data( pBuffer, width ) - pBuffer )) > 0)
        {
          wmove( win, row, 0 );
          waddnstr( win, pBuffer, len );
        }
    }