//
// Created by ethankuehler on 5/9/17.
//

#include "Functions.h"
#include "string"
#include "Solver.h"

extern "C"
{
    int START_SOLVER(char fileLocation[])
    {
        std::string file = fileLocation;
        try
        {
            Solver s(file);
            s.start();
        }
        catch (const std::exception& e)
        {
            return 1;
        }
        return  0;
    }
}