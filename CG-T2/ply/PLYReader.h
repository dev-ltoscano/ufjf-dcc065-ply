#ifndef PLYREADER_H_INCLUDED
#define PLYREADER_H_INCLUDED

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cmath>
#include <string>
#include <vector>

#include "PLYObject.h"

#include "../primitive/Triangle.h"
#include "../primitive/Quad.h"

class PLYReader
{
    public:
        // Lê um arquivo PLY
        PLYObject* read_ply_file(std::string ply_filepath);
};

#endif // PLYREADER_H_INCLUDED
