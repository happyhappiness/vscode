						ninitialized++;
				}

				if (ninitialized > 1) {
					/* Print merged arena stats. */
					malloc_cprintf(write_cb, cbopaque,
					    "\nMerged arenas stats:\n");
