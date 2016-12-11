#pragma once

#include "view.hpp"
#include "configuration.hpp"

class Media {
public:
    ~Media();

    static void initialize(Configuration::View viewConfiguration);
    static Media& instance();

    View makeView();

private:
    Media(Configuration::View viewConfiguration);

    static Media* _media;
    Configuration::View _viewConfiguration;
};

Media& media();