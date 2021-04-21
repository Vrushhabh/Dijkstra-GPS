//
// Created by Vrushhabh Patel on 4/20/21.
//

#pragma once
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "path_finder_map.h"

namespace pathfinder {
namespace graphics {

class Application : public ci::app::App {
  public:
    /**
     * The actual application that makes the UI of the project
     * Uses a lot of the same functions from the naives bayes assigment because the user
     * interacts similarly to the program
     */
    Application();
    void draw() override;
    void mouseDown(ci::app::MouseEvent event) override;
  private:
    const int kWindowSize = 800;
    // How much space is between the the edges of the window and between the spaces
    const double kMargin = 150;
    //How many spaces are in one side of the image
    const size_t kImageDimension = 20;
    //The visual map
    PathFinderMap map_;
};

}  // namespace visualizer

}  // namespace naivebayes



