int inflate(z, f)
z_stream *z;
int f;
{
  int r;
  uInt b;

  if (z == Z_NULL || z->next_in == Z_NULL)
    return Z_STREAM_ERROR;
  r = Z_BUF_ERROR;
  while (1) switch (z->state->mode)
  {
    case METHOD:
      NEEDBYTE
      if (((z->state->sub.method = NEXTBYTE) & 0xf) != DEFLATED)
      {
        z->state->mode = ZBAD;
        z->msg = "unknown compression method";
        z->state->sub.marker = 5;       /* can't try inflateSync */
        break;
      }
      if ((z->state->sub.method >> 4) + 8 > z->state->wbits)
      {
        z->state->mode = ZBAD;
        z->msg = "invalid window size";
        z->state->sub.marker = 5;       /* can't try inflateSync */
        break;
      }
      z->state->mode = FLAG;
    case FLAG:
      NEEDBYTE
      if ((b = NEXTBYTE) & 0x20)
      {
        z->state->mode = ZBAD;
        z->msg = "invalid reserved bit";
        z->state->sub.marker = 5;       /* can't try inflateSync */
        break;
      }
      if (((z->state->sub.method << 8) + b) % 31)
      {
        z->state->mode = ZBAD;
        z->msg = "incorrect header check";
        z->state->sub.marker = 5;       /* can't try inflateSync */
        break;
      }
      Trace((stderr, "inflate: zlib header ok\n"));
      z->state->mode = BLOCKS;
    case BLOCKS:
      r = inflate_blocks(z->state->blocks, z, r);
      if (f == Z_PACKET_FLUSH && z->avail_in == 0 && z->avail_out != 0)
	  r = inflate_packet_flush(z->state->blocks);
      if (r == Z_DATA_ERROR)
      {
        z->state->mode = ZBAD;
        z->state->sub.marker = 0;       /* can try inflateSync */
        break;
      }
      if (r != Z_STREAM_END)
        return r;
      r = Z_OK;
      inflate_blocks_reset(z->state->blocks, z, &z->state->sub.check.was);
      if (z->state->nowrap)
      {
        z->state->mode = DONE;
        break;
      }
      z->state->mode = CHECK4;
    case CHECK4:
      NEEDBYTE
      z->state->sub.check.need = (uLong)NEXTBYTE << 24;
      z->state->mode = CHECK3;
    case CHECK3:
      NEEDBYTE
      z->state->sub.check.need += (uLong)NEXTBYTE << 16;
      z->state->mode = CHECK2;
    case CHECK2:
      NEEDBYTE
      z->state->sub.check.need += (uLong)NEXTBYTE << 8;
      z->state->mode = CHECK1;
    case CHECK1:
      NEEDBYTE
      z->state->sub.check.need += (uLong)NEXTBYTE;

      if (z->state->sub.check.was != z->state->sub.check.need)
      {
        z->state->mode = ZBAD;
        z->msg = "incorrect data check";
        z->state->sub.marker = 5;       /* can't try inflateSync */
        break;
      }
      Trace((stderr, "inflate: zlib check ok\n"));
      z->state->mode = DONE;
    case DONE:
      return Z_STREAM_END;
    case ZBAD:
      return Z_DATA_ERROR;
    default:
      return Z_STREAM_ERROR;
  }

 empty:
  if (f != Z_PACKET_FLUSH)
    return r;
  z->state->mode = ZBAD;
  z->state->sub.marker = 0;       /* can try inflateSync */
  return Z_DATA_ERROR;
}