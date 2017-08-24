(ppmd_flags & 0x40)
    {
      if (!rar_br_read_ahead(a, br, 8))
        goto truncated_data;
      rar->ppmd_escape = rar->ppmd7_context.InitEsc = rar_br_bits(br, 8);
      rar_br_consume(br, 8);
    }
    else
      rar->ppmd_escape = 2