#-*-coding: utf-8 -*-
from jpype import *
import my_constant

class Gumtree:  
    gumtree = None

    def __init__(self, class_name='gumtree.GumTreeApi'):
        # class path
        jvm_arg = "-Djava.class.path=" + my_constant.JAVA_CLASS_PATH
        startJVM(getDefaultJVMPath(), '-d64', jvm_arg)
        # initial class and object
        GumtreeApi = JClass(class_name)
        Gumtree.gumtree = GumtreeApi()

    """
    @ param old and new file
    @ return
    @ involve set old and new file
    """
    def set_old_new_file(self, old_file, new_file):
        Gumtree.gumtree.setOldAndNewFile(old_file, new_file)

    """
    @ param line
    @ return flag about whether find old log
    @ involve set line for gumtree object
    """
    def set_old_loc(self, line):
        return Gumtree.gumtree.setOldLoc(line)

    """
    @ param 
    @ return line
    @ involve get mapping line of old log
    """
    def get_new_loc(self):
        return Gumtree.gumtree.getNewLoc()

    """
    @ param 
    @ return new log
    @ involve get mapping log of old log
    """
    def get_new_log(self):
        new_log = Gumtree.gumtree.getNewLog()
        if new_log is not None:
            return new_log + ';'
        else:
            return new_log
    """
    @ param 
    @ return old log
    @ involve get old log
    """
    def get_old_log(self):
        return Gumtree.gumtree.getOldLog() + ';'
      
    """
    @ param 
    @ return
    @ involve judge if log in old location has been edited
    """
    def is_old_log_edited(self):
        return Gumtree.gumtree.isOldLogEdited()

    """
    @ param line
    @ return flag about whether find new log
    @ involve set line for inserted node
    """
    def set_new_loc(self, line):
        return Gumtree.gumtree.setNewLoc(line)

    """
    @ param 
    @ return line
    @ involve get old loc for the inserted node
    """
    def get_old_loc(self):
        return Gumtree.gumtree.getOldLoc()

    """
    @ param old log locations
    @ return
    @ involve add log node into log nodes
    """
    def add_old_log_nodes(self, lines):
        for line in lines:
            Gumtree.gumtree.addOldLogNode(line)

    """
    @ param new log locations
    @ return
    @ involve add log node into log nodes
    """
    def add_new_log_nodes(self, lines):
        for line in lines:
            Gumtree.gumtree.addNewLogNode(line)

    """
    @ param 
    @ return
    @ involve get action type
    """
    def get_hunk_edited_type(self):
        return Gumtree.gumtree.getActionType()

    """
    @ param filename
    @ return
    @ involve set file
    """
    def set_file(self, filename):
        Gumtree.gumtree.setFile(filename)

    """
    @ param line
    @ return flag about whether success
    @ involve set loccation of log
    """
    def set_loc(self, line):
        return Gumtree.gumtree.setLoc(line)

    """
    @ param
    @ return
    @ involve get log statement
    """
    def get_log(self):
        return Gumtree.gumtree.getLog() + ';'

    """
    @ param
    @ return
    @ involve get block which contains log
    """
    def get_block(self):
        return Gumtree.gumtree.getBlock()

    """
    @ param
    @ return
    @ involve get block which contains log
    """
    def get_function(self):
        return Gumtree.gumtree.getFunction()

    """
    @ param
    @ return
    @ involve get block which contains log
    """
    def get_function_loc(self):
        return Gumtree.gumtree.getFunctionLoc()

    """
    @ param
    @ return
    @ involve get feature vector for block[type vs frequence]
    """
    def get_block_feature(self):
        vector_str = Gumtree.gumtree.getBlockFeature()
        vector = vector_str[1:-1].split(",")
        vector = [int(i) for i in vector]
        return vector

    """
    @ param
    @ return
    @ involve get type vector of block
    """
    def get_block_type(self):
        return Gumtree.gumtree.getBlockType()
    """
    @ param old and new log file
    @ return flag about match or not
    @ involve just update action
    """
    def is_match(self, old_log_file, new_log_file):
        Gumtree.gumtree.setOldAndNewFile(old_log_file, new_log_file)
        return Gumtree.gumtree.isMatch()

    """
    @ param old and new log file, and repos log file
    @ return flag about match or not
    @ involve no action allowed in edited node
    """
    def is_match_with_edit(self, old_log_file, new_log_file, repos_log_file):
        Gumtree.gumtree.setOldAndNewFile(old_log_file, new_log_file)
        Gumtree.gumtree.getEditedNodes()
        return Gumtree.gumtree.isMatchWithEdit(repos_log_file)
    """
    @ param 
    @ return
    @ involve close jvm
    """
    def close(self):
        shutdownJVM()


"""
main function
"""
if __name__ == "__main__":
    old_file = 'second/gumtree/c/old.cpp'
    new_file = 'second/gumtree/c/new.cpp'
    gumtree = Gumtree()
    gumtree.set_old_loc(7)
    gumtree.get_new_log()
  