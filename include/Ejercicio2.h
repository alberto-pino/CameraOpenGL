#pragma once

#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "GLInclude.h"
#include "camera.h"
#include "shapes.h"

void drawLine(LINE line, COLOUR color = grey, bool doDrawDots
	= false);

void drawAxis();