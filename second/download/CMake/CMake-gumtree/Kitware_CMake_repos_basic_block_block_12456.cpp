{
      i++;
      client_offset += rar->dbo[i].start_offset - rar->dbo[i-1].end_offset;
    }