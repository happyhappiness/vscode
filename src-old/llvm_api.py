#-*-coding: utf-8 -*-
import commands
import my_constant
import myUtil
import re

class LLVM:  
    load_llvm_lib = 'opt -load=/opt/llvm-build/lib/LLVMMyTryPass.so -mypass '

    def __init__(self, log_loc=0, in_bc=''):
        self.log_loc = str(log_loc + 1) # index from 1
        self.in_file = in_bc
        self.cdg_list = []
        self.ddg_list = []

    """
    @ param log location
    @ return
    @ involve set log location for object
    """
    def set_log_loc(self, log_loc):
        self.log_loc = str(log_loc + 1) # index from 1

    """
    @ param
    @ return log location
    @ involve get log location for object
    """
    def get_log_loc(self):
        return self.log_loc

    """
    @ param input binarycode file
    @ return
    @ involve set input .bc file
    """
    def set_in_file(self, in_bc):
        self.in_file = in_bc

    """
    @ param
    @ return input .bc file name
    @ involve get input .bc file
    """
    def get_in_file(self):
        return self.in_file

    """
    @ param lib path
    @ return
    @ involve set lib path for class
    """
    def set_load_llvm_lib(self, load_llvm_lib):
        LLVM.load_llvm_lib = load_llvm_lib

    """
    @ param
    @ return lib path
    @ involve get lib path for class
    """
    def get_load_llvm_lib(self):
        return LLVM.load_llvm_lib


    """
    @ param
    @ return cdg list and ddg list
    @ involve call llvm lib and process result
    """
    def get_cdg_ddg_list(self):
        if self.log_loc == '0':
            return [], []
        # call lib with opt command, param: bc file and location
        load_command = LLVM.load_llvm_lib + self.in_file + ' -loc ' + self.log_loc + ' > /dev/null'
        output = commands.getoutput(load_command)
        # analyze shell output
        self.__analyze_cdg_ddg_list(output)
        if self.cdg_list == [] and self.ddg_list == []:
            print output
        return self.cdg_list, self.ddg_list

    """
    @ param
    @ return
    @ involve analyze shell output and update cdg and ddg list
    """
    def __analyze_cdg_ddg_list(self, shell_output):
        self.cdg_list = []
        self.ddg_list = []
        shell_output = shell_output.split('\n')
        # mark not found
        if len(shell_output) == 1:
            self.cdg_list = [-1]
            self.ddg_list = [-1]
            return
        size = len(shell_output)
        for i in range(size):
            line = shell_output[i]
            # find @cdg@
            if line.startswith('@cdg@') and i < size - 1:
                self.cdg_list = shell_output[i+1].split('\t')[:-1]
            # find @ddg@
            if line.startswith('@ddg@') and i < size - 1:
                self.ddg_list = shell_output[i+1].split('\t')[:-1]

"""
main function
"""
if __name__ == "__main__":
    in_bc = '/usr/info/code/cpp/LogMonitor/LogMonitor/clang/hello.bc'
    log_loc = 34
    llvm_api = LLVM(log_loc, in_bc)
    cdg, ddg = llvm_api.get_cdg_ddg_list()
    print 'cdg is: '
    print cdg
    print 'ddg is: '
    print ddg
