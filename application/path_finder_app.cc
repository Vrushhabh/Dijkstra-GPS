//
// Created by Vrushhabh Patel on 4/20/21.
//
#include "string"
#include <iostream>

#include <graphics/application.h>

using pathfinder::graphics::Application;

void prepareSettings(Application::Settings* settings) {
    settings->setResizable(false);
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(Application, ci::app::RendererGl, prepareSettings);
