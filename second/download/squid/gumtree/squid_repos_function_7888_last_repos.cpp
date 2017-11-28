boolean
group_in_compile_stack(compile_stack_type compile_stack, regnum_t regnum)
{
    int this_element;

    for (this_element = compile_stack.avail - 1;
            this_element >= 0;
            this_element--)
        if (compile_stack.stack[this_element].regnum == regnum)
            return true;

    return false;
}