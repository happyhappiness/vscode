#-*-coding: utf-8 -*-
from jpype import *
import os

import my_constant

def simple_test():
    """"simple test about invoking jdk methods"""

    startJVM(getDefaultJVMPath())
    java.lang.System.out.println("hello java in python")
    shutdownJVM()

def jar_test():
    """"test about invoke packaged jar"""
    # class path
    jvm_arg = "-Djava.class.path=" + my_constant.JAVA_CLASS_PATH
    startJVM(getDefaultJVMPath(), '-d64', jvm_arg)
    # initial class and object
    gumtree_api = JClass('gumtree.GumTreeApi')
    gumtree = gumtree_api()
    # call method
    old_file = '/data/gumtree/java/SayHello.java'
    new_file = '/data/gumtree/java/SayHelloWorld.java'
    gumtree.getAction(old_file, new_file)
    gumtree.getMapping(old_file, new_file)
    shutdownJVM()

# simple_test()
jar_test()
