#ifndef FEATURE_TRACKER__H
#defien FEATURE_TRACKER__H

#include "feature_detector.h"
#include "point_matcher.h"

class FeatureTracker
{
	FeatureDetector feature_detector;
	PointMatcher point_matcher;
}

#endif