%module knightdom

%include <std_string.i>
%include <std_vector.i>

%{
/* Includes the header in the wrapper code */

#include "boardgame.h"
#include "knightdom.h"

%}

/* Parse the header file to generate wrappers */

%include "boardgame.h"
%include "knightdom.h"
