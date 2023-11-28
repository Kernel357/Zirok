#!/bin/python

from sys import platform
import shutil
import subprocess 
from datetime import datetime

def main():
    subprocess.run(["clear"])
    print("****************************************************************")
    print("Hello! This is a script for automatic build of the Zirok Project") 
    print("****************************************************************")
    print("Date: ", datetime.now())
    
    
    # SET TARGET
    TARGET = input("Set a TARGET (Release - \"1\" / Debug - \"2\"): ")
    
    if TARGET == "1":
        TARGET = "Release"
    
    elif TARGET == "2":
        TARGET = "Debug"
    
    else:
        print("Invalid TARGET")
        return
    
    
    # SET DebugLib 
    USE_LOG_FILE = "0"
    if TARGET == "Debug": 
        USE_LOG_FILE = input("Set a DebugLib (Log to file - \"1\" / Log to STDOUT - \"2\"): ")
    
        if USE_LOG_FILE != "1" and USE_LOG_FILE != "2":
            print("Invalid USE_LOG_FILE")
            return
        
    
    # SET PLATFORM
    PLATFORM = input("Set a PLATFORM (Linux - \"1\" / Windows - \"2\"): ")
        
    if PLATFORM == "1":
        linux_build(TARGET, USE_LOG_FILE)
    
    elif PLATFORM == "2":
        win_build(TARGET, USE_LOG_FILE)
        
    else:
        print("Invalid PLATFORM")
        return
            
    return
    
        
def linux_build(TARGET, USE_LOG_FILE):     
    PATH = "Build/" + TARGET
    subprocess.run(["cmake", "-S", ".", "-B", PATH, "-D", "CMAKE_BUILD_TYPE=" + TARGET, "-D", "USE_LOG_FILE=" + USE_LOG_FILE])
    subprocess.run(["cmake", "--build", PATH, "--config", TARGET, "--target", "all"])
    
    return 0
    
def win_build(TARGET, USE_LOG_FILE):
    return 0

main()

