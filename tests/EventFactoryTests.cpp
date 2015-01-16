//  Created by Alejandro Isaza on 2014-05-20.
//  Copyright (c) 2014 Venture Media Labs. All rights reserved.

#include <lxml/lxml.h>
#include <mxml/parsing/ScoreHandler.h>
#include <mxml/EventFactory.h>

#include <fstream>
#include <boost/test/unit_test.hpp>
#include <unistd.h>

using namespace mxml;

 BOOST_AUTO_TEST_CASE(moonlight) {
     ScoreHandler handler;
     std::ifstream is("moonlight.xml");
     lxml::parse(is, "moonlight.xml", handler);
    
     const dom::Score& score = *handler.result();
     ScoreProperties scoreProperties(score);

     EventFactory factory(score, scoreProperties);
     auto events = factory.build();

     // Total number of events including repeats
     BOOST_CHECK_EQUAL(events->events().size(), 3711);
    
     BOOST_CHECK_EQUAL(scoreProperties.tempo(0, 0), 160);
     BOOST_CHECK_CLOSE(scoreProperties.tempo(13, 240), 80, 0.01);
     BOOST_CHECK_EQUAL(scoreProperties.tempo(14, 0), 160);
 }
