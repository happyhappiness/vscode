 
 		num_to_alloc = (yy_buffer_stack_max) + grow_size;
 		(yy_buffer_stack) = (struct yy_buffer_state**)yyrealloc
 								((yy_buffer_stack),
 								num_to_alloc * sizeof(struct yy_buffer_state*)
 								);
-		if ( ! (yy_buffer_stack) )
-			YY_FATAL_ERROR( "out of dynamic memory in yyensure_buffer_stack()" );
 
 		/* zero only the new slots.*/
 		memset((yy_buffer_stack) + (yy_buffer_stack_max), 0, grow_size * sizeof(struct yy_buffer_state*));
 		(yy_buffer_stack_max) = num_to_alloc;
 	}
 }
