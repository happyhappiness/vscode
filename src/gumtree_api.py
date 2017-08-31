#-*-coding: utf-8 -*-
from jpype import *
import my_constant
import myUtil
import re

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
    @ param old and new log file
    @ return list of edited word pair
    @ involve ast node edition -> word edition(literal split with space)
    """
    def get_word_edit(self, old_log_file, new_log_file):
        Gumtree.gumtree.setOldAndNewFile(old_log_file, new_log_file)
        edit_elements = set(Gumtree.gumtree.getWordEdit())
        edit_words = []
        edit_feature = []
        for edit_element in edit_elements:
            old_element = edit_element[0]
            new_element = edit_element[1]
            edit_words.append([old_element, new_element])
            edit_feature.append(abs(hash(new_element.lower()) - hash(old_element.lower())))

        return edit_words, edit_feature

    """ 
        # split to get list of words
        log_spliter = r'[^\w%]'
        old_log = myUtil.remove_given_element('', re.split(log_spliter, old_log))
        new_log = myUtil.remove_given_element('', re.split(log_spliter, new_log))
        # get edit
        edit_words = []
        edit_feature = []
        length_old = len(old_log)
        length_new = len(new_log)
        length = max(length_old, *)
        for i in range(length):
            if i < length_old and i < length_new and old_log[i] == new_log[i]:
                continue

            if i < length_old:
                old_element = old_log[i]
            else:
                old_element = ''
            if i < length_new:
                new_element = new_log[i]
            else:
                new_element = ''

            edit_words.append([old_element, new_element])
            edit_feature.append(abs(hash(new_element.lower()) - hash(old_element.lower())))

        print edit_words
        print edit_feature 
    """

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
    # gumtree.set_old_loc(7)
    # gumtree.get_new_log()
    gumtree.get_word_edit('printf("unknown")', 'printf("unkonwn")')
    gumtree.get_word_edit('printf("unkonwn")', 'printf("unknown")')
    gumtree.get_word_edit('archive_string_sprintf(a_estr, errstr, path);', 'archive_string_sprintf(a_estr, "%s%s", errstr, path);')
    


  