(rar->dbo[rar->cursor].start_offset < 0)
    {
      rar->dbo[rar->cursor].start_offset = a->filter->position;
      rar->dbo[rar->cursor].end_offset = rar->dbo[rar->cursor].start_offset +
        rar->packed_size;
    }