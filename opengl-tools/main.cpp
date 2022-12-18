//
//  main.cpp
//  openGL_tools
//
//  Created by Frank Collebrusco on 12/14/22.
//
#include <iostream>
#include "Engine/Context.h"

int main(int argc, const char * argv[]) {
    context_init();
    context_loop();
    context_close();
}

