(zisofs->block_pointers_avail
			    == zisofs->block_pointers_size) {
				/* We've got all block pointers and initialize
				 * related variables.	*/
				zisofs->block_off = 0;
				zisofs->block_avail = 0;
				/* Complete a initialization */
				zisofs->initialized = 1;
			}