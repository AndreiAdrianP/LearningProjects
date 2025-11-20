#!/bin/bash

#---Configuration----------
BUILD_DIR="build"
EXECUTABLE_NAME="RAIIdemo"

#-------Functions---------
#Clean build--------------
clean_build(){
    echo "---Cleaning build directory---"
    if [ -d "$BUILD_DIR" ]; then
        rm -rf "$BUILD_DIR"
        echo "Removed build directory: $BUILD_DIR "
    fi
    echo "Clean complete."

}

#Configure CMake project---
configure_project(){
    echo "---Configuring project---"
    #Create buid dir if it doesn't exist
    mkdir -p "$BUILD_DIR"
    #Cmake needs to run in the build dir so we change dir
    cd "$BUILD_DIR" || exit 1
    cmake ..
    if [ $? -ne 0 ]; then
        echo "Configuration failed"
        exit 1
    fi
    cd ..
    echo "Configuration succesful."
}

#Build the project------
build_project(){
    echo "---Building project---"
    cd "$BUILD_DIR" || exit 1
    make 
    if [ $? -ne 0 ]; then
        echo "Build failed"
        exit 1
    fi
    cd ..
    echo "Build succesful."

}

#Run project ----
run_project(){
    echo "---Running $EXECUTABLE_NAME ---"
    ./$BUILD_DIR/$EXECUTABLE_NAME
}

#-----Main script logic ------
if [ "$#" -eq 0 ]; then
    echo "/build.sh [clean|config|build|run|all]"
    exit 1
fi

case "$1" in
    clean)
        clean_build
        ;;
    config)
        configure_project
        ;;
    build)
        build_project
        ;;
    run)
        run_project
        ;;
    all)
        clean_build
        configure_project
        build_project
        run_project
        ;;
    *)
        echo "Invalid command: $1"
        echo "Usage: ./BashBuild.sh [clean|config|build|run|all]"
        exit 1
        ;;
esac