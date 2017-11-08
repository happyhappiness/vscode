void h2_task_input_block_set(h2_task_input *input, apr_read_type_e block)
{
    input->block = block;
}