{
					/* We have decoded all blocks.
					 * Let's handle next blocks. */
					ds->state = ST_RD_BLOCK;
					ds->br = bre;
					ds->blocks_avail = 0;
					ds->w_pos = w_pos;
					ds->copy_pos = 0;
					return (100);
				}